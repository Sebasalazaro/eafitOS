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
 * Elimina un archivo del sistema de archivos utilizando la función remove().
 * Versión simple sin confirmación (usa el comando 'estadisticas' para ver info antes).
 * 
 * @param args args[1] debe contener el nombre del archivo a eliminar.
 */
void cmd_eliminar(char **args) {
    // Validación: ¿El usuario proporcionó el nombre del archivo?
    if (args[1] == NULL) {
        imprimir_error("Debes especificar un archivo para eliminar.");
        printf("Uso: eliminar <nombre_archivo>\n");
        printf("Ejemplo: eliminar test.txt\n");
        printf("\nTip: Usa 'estadisticas <archivo>' para ver info antes de eliminar.\n");
        return;
    }

    // remove(): Función estándar de C que elimina el archivo especificado.
    // Retorna 0 si tuvo éxito, o un valor distinto de 0 si falló.
    // La función trabaja con el sistema de archivos del OS mediante syscalls.
    if (remove(args[1]) == 0) {
        // Éxito: El archivo fue eliminado correctamente
        char mensaje[256];
        snprintf(mensaje, sizeof(mensaje), "Archivo '%s' eliminado correctamente", args[1]);
        imprimir_exito(mensaje);
    } else {
        // Error: No se pudo eliminar (archivo no existe, permisos insuficientes, etc.)
        char mensaje[256];
        snprintf(mensaje, sizeof(mensaje), "No se pudo eliminar '%s'", args[1]);
        imprimir_error(mensaje);
        perror("Razón");
    }
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

    // 3. Formatear el tamaño del archivo de manera legible
    double tamano = (double)info.st_size;
    char tamano_str[50];
    
    if (tamano < 1024) {
        snprintf(tamano_str, sizeof(tamano_str), "%.0f bytes", tamano);
    } else if (tamano < 1024 * 1024) {
        snprintf(tamano_str, sizeof(tamano_str), "%.2f KB (%.0f bytes)", tamano / 1024, tamano);
    } else if (tamano < 1024 * 1024 * 1024) {
        snprintf(tamano_str, sizeof(tamano_str), "%.2f MB (%.0f bytes)", tamano / (1024 * 1024), tamano);
    } else {
        snprintf(tamano_str, sizeof(tamano_str), "%.2f GB (%.0f bytes)", tamano / (1024 * 1024 * 1024), tamano);
    }

    // 4. Formatear fechas importantes
    // localtime() convierte timestamps UNIX a estructuras de tiempo legibles
    // strftime() formatea la estructura como cadena personalizada
    char fecha_modificacion[100];
    char fecha_acceso[100];
    char fecha_cambio[100];
    
    struct tm *tm_info;
    
    tm_info = localtime(&info.st_mtime); // Ultima modificación de contenido
    strftime(fecha_modificacion, sizeof(fecha_modificacion), "%d/%m/%Y %H:%M:%S", tm_info);
    
    tm_info = localtime(&info.st_atime); // Ultimo acceso (lectura)
    strftime(fecha_acceso, sizeof(fecha_acceso), "%d/%m/%Y %H:%M:%S", tm_info);
    
    tm_info = localtime(&info.st_ctime); // Ultimo cambio de metadatos
    strftime(fecha_cambio, sizeof(fecha_cambio), "%d/%m/%Y %H:%M:%S", tm_info);

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
