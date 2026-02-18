/**
 * @file advanced_commands.c
 * @brief Comandos avanzados del sistema.
 * 
 * Contiene comandos adicionales como historial, crear archivos, etc.
 */

#include <stdio.h>
#include <string.h>     // Para strcpy, strlen
#include <sys/stat.h>   // Para stat() - información de archivos
#include <time.h>       // Para formatear fechas
#include "commands.h"
#include "ui.h"         // Colores y formato

// --- Variables Globales para Historial ---
#define MAX_HISTORIAL 10
#define MAX_CMD_LEN 256

// Buffer estático: cada fila es un comando
static char historial[MAX_HISTORIAL][MAX_CMD_LEN];
// Contador de comandos totales ejecutados
static int contador_historial = 0;

// --- Funciones Helper para Manejo de Archivos ---

/**
 * @brief Formatea un tamaño en bytes a una representación legible.
 * 
 * Convierte bytes a la unidad más apropiada (bytes, KB, MB, GB) para facilitar
 * la lectura humana. Esta función es reutilizable en cualquier comando que
 * necesite mostrar tamaños de archivo.
 * 
 * @param bytes Tamaño en bytes a formatear.
 * @param buffer Buffer donde se escribirá el resultado.
 * @param size Tamaño del buffer.
 */
void formatear_tamano(double bytes, char *buffer, size_t size) {
    if (bytes < 1024) {
        snprintf(buffer, size, "%.0f bytes", bytes);
    } else if (bytes < 1024 * 1024) {
        snprintf(buffer, size, "%.2f KB", bytes / 1024);
    } else if (bytes < 1024 * 1024 * 1024) {
        snprintf(buffer, size, "%.2f MB", bytes / (1024 * 1024));
    } else {
        snprintf(buffer, size, "%.2f GB", bytes / (1024 * 1024 * 1024));
    }
}

/**
 * @brief Formatea un timestamp UNIX a formato legible dd/mm/yyyy hh:mm:ss.
 * 
 * Convierte un time_t (timestamp UNIX) a una cadena de texto legible.
 * Esta función encapsula la conversión de localtime() + strftime() para
 * reutilización en múltiples comandos.
 * 
 * @param timestamp Timestamp UNIX (segundos desde el epoch).
 * @param buffer Buffer donde se escribirá el resultado.
 * @param size Tamaño del buffer.
 */
void formatear_fecha(time_t timestamp, char *buffer, size_t size) {
    struct tm *tm_info = localtime(&timestamp);
    strftime(buffer, size, "%d/%m/%Y %H:%M:%S", tm_info);
}

/**
 * @brief Agrega un comando al historial circular.
 * 
 * Esta función se llama automáticamente desde shell_loop.c cada vez
 * que se ejecuta un comando válido. No es invocada por el usuario directamente.
 * 
 * Funciona como un buffer circular: cuando llega al comando 11,
 * sobrescribe el comando 1 (el más antiguo).
 * 
 * @param comando Cadena con el comando a guardar.
 */
void agregar_al_historial(const char *comando) {
    // Validar que el comando no sea NULL y no esté vacío
    if (comando == NULL || strlen(comando) == 0) {
        return;
    }
    
    // Calcular la posición usando módulo (operador %) para que el índice "dé la vuelta" después de 10
    int indice = contador_historial % MAX_HISTORIAL;
    
    // strncpy: Copia hasta MAX_CMD_LEN-1 caracteres de forma segura
    // El -1 es para dejar espacio al terminador '\0'
    strncpy(historial[indice], comando, MAX_CMD_LEN - 1);
    
    // Asegurar que la cadena termine en '\0' (null terminator)
    historial[indice][MAX_CMD_LEN - 1] = '\0';
    
    // Incrementar el contador global
    contador_historial++;
}

/**
 * @brief Comando HISTORIAL
 * 
 * Muestra los últimos 10 comandos ejecutados, numerados del más reciente al más antiguo.
 * 
 * @param args Argumentos del comando (ignorados).
 */
void cmd_historial(char **args) {
    printf("\n");
    printf(COLOR_CYAN "=== Historial de Comandos ===" COLOR_RESET "\n");
    imprimir_separador();
    
    // Si no se han ejecutado comandos aún:
    if (contador_historial == 0) {
        printf(COLOR_AMARILLO "  (El historial está vacío)\n" COLOR_RESET);
        printf("\n");
        (void)args;
        return;
    }
    
    // Determinar cuántos comandos mostrar (máximo 10)
    int total = contador_historial < MAX_HISTORIAL ? contador_historial : MAX_HISTORIAL;
    
    // Recorrer desde el más reciente al más antiguo
    for (int i = 0; i < total; i++) {
        // Calcular el índice "hacia atrás" en el buffer circular (1 es el más reciente, 10 el más antiguo)
        int indice = (contador_historial - 1 - i) % MAX_HISTORIAL;
        
        // Asegurar que el índice sea positivo (fix para módulo negativo en C)
        if (indice < 0) {
            indice += MAX_HISTORIAL;
        }
        
        // Mostrar con numeración y color
        printf(COLOR_VERDE "%2d." COLOR_RESET " %s\n", i + 1, historial[indice]);
    }
    
    imprimir_separador();
    printf("\n");
    (void)args;
}


/**
 * @brief Comando CREAR
 * 
 * Crea un archivo vacío en el directorio actual.
 * Si el archivo ya existe, lo sobrescribe sin preguntar.
 * 
 * Utiliza fopen() en modo "w" (write), que:
 * - Crea el archivo si no existe
 * - Lo trunca (vacía) si ya existe
 * - Retorna NULL si hay error (ej: permisos insuficientes)
 * 
 * @param args args[1] debe contener el nombre del archivo a crear.
 */
void cmd_crear(char **args) {
    // 1. Validación: ¿El usuario proporcionó el nombre del archivo?
    if (args[1] == NULL) {
        imprimir_error("Debes especificar un nombre de archivo");
        printf("Uso: crear <nombre_archivo>\n");
        printf("Ejemplo: crear test.txt\n");
        return;
    }

    // 2. Intentar crear el archivo
    FILE *fp = fopen(args[1], "w");
    
    // 3. Verificar si hubo error
    if (fp == NULL) {
        char mensaje[256];
        snprintf(mensaje, sizeof(mensaje), "No se pudo crear '%s'", args[1]);
        imprimir_error(mensaje);
        perror("Razón");
        return;
    }

    // 4. Éxito: mensaje de confirmación
    char mensaje[256];
    snprintf(mensaje, sizeof(mensaje), "Archivo '%s' creado correctamente", args[1]);
    imprimir_exito(mensaje);
    
    // 5. Cerrar el archivo
    fclose(fp);
}

/**
 * @brief Comando ELIMINAR (rm)
 * 
 * Elimina un archivo del sistema de archivos con confirmación previa.
 * Antes de eliminar, muestra información del archivo (tamaño, fecha de modificación)
 * para que el usuario pueda verificar que es el archivo correcto.
 * 
 * @param args args[1] debe contener el nombre del archivo a eliminar.
 */
void cmd_eliminar(char **args) {
    // 1. Validación: ¿El usuario proporcionó el nombre del archivo?
    if (args[1] == NULL) {
        imprimir_error("Debes especificar un archivo para eliminar.");
        printf("Uso: eliminar <nombre_archivo>\n");
        printf("Ejemplo: eliminar test.txt\n");
        return;
    }

    // 2. Obtener información del archivo usando stat()
    // stat() es una syscall que retorna información detallada de un archivo
    struct stat info_archivo;
    
    // stat(ruta, &estructura): retorna 0 si existe, -1 si no existe o hay error
    if (stat(args[1], &info_archivo) != 0) {
        char mensaje[256];
        snprintf(mensaje, sizeof(mensaje), "El archivo '%s' no existe", args[1]);
        imprimir_error(mensaje);
        return;
    }

    // 3. Formatear información del archivo usando funciones helper
    char tamano_str[50];
    char fecha_str[100];
    
    formatear_tamano((double)info_archivo.st_size, tamano_str, sizeof(tamano_str));
    formatear_fecha(info_archivo.st_mtime, fecha_str, sizeof(fecha_str));

    // 4. Mostrar información del archivo para confirmación
    printf("\n");
    printf(COLOR_AMARILLO "⚠ Confirmación de eliminación\n" COLOR_RESET);
    printf(COLOR_DIM "────────────────────────────────────────────────────────────\n" COLOR_RESET);
    printf("  " COLOR_CYAN "Archivo:" COLOR_RESET "            %s\n", args[1]);
    printf("  " COLOR_CYAN "Tamaño:" COLOR_RESET "             %s\n", tamano_str);
    printf("  " COLOR_CYAN "Última modificación:" COLOR_RESET " %s\n", fecha_str);
    printf(COLOR_DIM "────────────────────────────────────────────────────────────\n" COLOR_RESET);

    // 5. Pedir confirmación al usuario
    printf("\n¿Estás seguro de eliminar este archivo? (s/n): ");
    
    // Leer respuesta del usuario
    // getchar() lee un solo carácter desde la entrada estándar
    char respuesta = getchar();
    
    // Limpiar el buffer de entrada (eliminar el '\n' que quedó)
    while (getchar() != '\n');

    // 6. Verificar respuesta y proceder
    if (respuesta == 's' || respuesta == 'S' || respuesta == 'y' || respuesta == 'Y') {
        // Usuario confirmó: proceder a eliminar
        // remove(): Función estándar de C que elimina el archivo (syscall unlink/remove)
        if (remove(args[1]) == 0) {
            char mensaje[256];
            snprintf(mensaje, sizeof(mensaje), "Archivo '%s' eliminado correctamente", args[1]);
            imprimir_exito(mensaje);
        } else {
            // Este caso es raro si stat() funcionó, pero puede pasar (permisos, disco lleno, etc.)
            char mensaje[256];
            snprintf(mensaje, sizeof(mensaje), "Error inesperado al eliminar '%s'", args[1]);
            imprimir_error(mensaje);
            perror("Razón");
        }
    } else {
        // Usuario canceló la operación
        imprimir_info("Operación cancelada. No se eliminó ningún archivo.");
    }
    
    printf("\n");
}

/**
 * @brief Comando ESTADISTICAS (stat)
 * 
 * Muestra información detallada de un archivo utilizando la syscall stat().
 * Incluye: tamaño, permisos, fechas de acceso/modificación/cambio, inodo, etc.
 * 
 * Este comando es útil para:
 * - Verificar información de un archivo antes de eliminarlo
 * - Ver metadatos del sistema de archivos
 * - Aprender cómo el OS almacena información de archivos
 * 
 * @param args args[1] debe contener el nombre del archivo a inspeccionar.
 */
void cmd_estadisticas(char **args) {
    // 1. Validación: ¿El usuario proporcionó el nombre del archivo?
    if (args[1] == NULL) {
        imprimir_error("Debes especificar un archivo.");
        printf("Uso: estadisticas <nombre_archivo>\n");
        printf("Ejemplo: estadisticas README.md\n");
        return;
    }

    // 2. Obtener información del archivo usando stat()
    // stat() es una syscall POSIX que retorna metadatos completos de un archivo
    // struct stat contiene: tamaño, permisos, dueño, fechas, tipo, inodo, etc.
    struct stat info;
    
    // stat(ruta, &estructura): retorna 0 si existe, -1 si no existe o hay error
    if (stat(args[1], &info) != 0) {
        char mensaje[256];
        snprintf(mensaje, sizeof(mensaje), "No se pudo acceder a '%s'", args[1]);
        imprimir_error(mensaje);
        perror("Razón");
        return;
    }

    // 3. Formatear el tamaño usando la función helper
    char tamano_str[50];
    formatear_tamano((double)info.st_size, tamano_str, sizeof(tamano_str));

    // 4. Formatear las 3 fechas importantes usando la función helper
    char fecha_modificacion[100];
    char fecha_acceso[100];
    char fecha_cambio[100];
    
    formatear_fecha(info.st_mtime, fecha_modificacion, sizeof(fecha_modificacion)); // Ultima modificación
    formatear_fecha(info.st_atime, fecha_acceso, sizeof(fecha_acceso));             // Ultimo acceso
    formatear_fecha(info.st_ctime, fecha_cambio, sizeof(fecha_cambio));             // Cambio de metadatos

    // 5. Determinar el tipo de archivo (usando macros de <sys/stat.h>)
    const char *tipo;
    if (S_ISREG(info.st_mode)) {
        tipo = "Archivo regular";
    } else if (S_ISDIR(info.st_mode)) {
        tipo = "Directorio";
    } else if (S_ISLNK(info.st_mode)) {
        tipo = "Enlace simbólico";
    } else if (S_ISCHR(info.st_mode)) {
        tipo = "Dispositivo de caracteres";
    } else if (S_ISBLK(info.st_mode)) {
        tipo = "Dispositivo de bloques";
    } else if (S_ISFIFO(info.st_mode)) {
        tipo = "FIFO (named pipe)";
    } else if (S_ISSOCK(info.st_mode)) {
        tipo = "Socket";
    } else {
        tipo = "Desconocido";
    }

    // 6. Formatear permisos en notación octal (ej: 0644, 0755)
    unsigned int permisos = info.st_mode & 0777; // Máscara para obtener solo bits de permisos

    // 7. Mostrar toda la información formateada con diseño mejorado
    const char *separador = "────────────────────────────────────────────────────────────";
    
    printf("\n");
    printf(COLOR_CYAN ESTILO_NEGRITA "=== Estadísticas de Archivo ===" COLOR_RESET "\n");
    printf(COLOR_DIM "%s" COLOR_RESET "\n", separador);

    printf(COLOR_VERDE "Archivo:" COLOR_RESET "            %s\n", args[1]);
    printf(COLOR_VERDE "Tipo:" COLOR_RESET "               %s\n", tipo);
    printf(COLOR_VERDE "Tamaño:" COLOR_RESET "             %s\n", tamano_str);
    printf(COLOR_VERDE "Permisos:" COLOR_RESET "           %04o\n", permisos);
    printf(COLOR_VERDE "Inodo:" COLOR_RESET "              %lu\n", (unsigned long)info.st_ino);
    printf(COLOR_VERDE "Enlaces:" COLOR_RESET "            %lu\n", (unsigned long)info.st_nlink);
    
    printf("\n");
    printf(COLOR_VERDE "Fechas:\n" COLOR_RESET);
    printf("  Modificación:      %s\n", fecha_modificacion);
    printf("  Acceso:            %s\n", fecha_acceso);
    printf("  Cambio (metadata): %s\n", fecha_cambio);
    
    printf(COLOR_DIM "%s" COLOR_RESET "\n", separador);
    printf("\n");
}
