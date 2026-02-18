/**
 * @file helpers.c
 * @brief Funciones auxiliares reutilizables del sistema.
 * 
 * Este archivo contiene funciones helper que son utilizadas por múltiples
 * comandos, promoviendo la reutilización de código y el principio DRY
 * (Don't Repeat Yourself).
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "utils.h"

/**
 * @brief Formatea un tamaño en bytes a una representación legible.
 * 
 * Convierte bytes a la unidad más apropiada (bytes, KB, MB, GB) para facilitar la lectura humana
 * 
 * @param bytes Tamaño en bytes a formatear.
 * @param buffer Buffer donde se escribirá el resultado.
 * @param size Tamaño del buffer (debe ser al menos 50 caracteres).
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
 * Ejemplo:
 * - 1708300800 → "18/02/2026 10:00:00"
 * 
 * @param timestamp Timestamp UNIX (segundos desde el epoch - 1 enero 1970).
 * @param buffer Buffer donde se escribirá el resultado.
 * @param size Tamaño del buffer (debe ser al menos 100 caracteres).
 */
void formatear_fecha(time_t timestamp, char *buffer, size_t size) {
    struct tm *tm_info = localtime(&timestamp);
    strftime(buffer, size, "%d/%m/%Y %H:%M:%S", tm_info);
}


/**
 * @brief Verifica si un archivo existe y es accesible.
 * 
 * Utiliza la syscall stat() para verificar la existencia de un archivo.
 * Es más eficiente que intentar abrir el archivo y verificar si falla.
 * 
 * @param ruta Ruta del archivo a verificar.
 * @return 1 si el archivo existe, 0 si no existe o no es accesible.
 */
int archivo_existe(const char *ruta) {
    struct stat info;
    return (stat(ruta, &info) == 0);
}


/**
 * @brief Valida que un argumento específico exista en la lista de argumentos.
 * 
 * Función helper para simplificar la validación de argumentos en comandos.
 * Si el argumento no existe, imprime un mensaje de error y retorna 0.
 * 
 * @param args Array de argumentos del comando.
 * @param indice Índice del argumento a validar (1 para el primer arg después del comando).
 * @param uso_msg Mensaje de uso a mostrar si la validación falla.
 * @return 1 si el argumento existe, 0 si es NULL.
 */
int validar_argumento(char **args, int indice, const char *uso_msg) {
    if (args[indice] == NULL) {
        printf("Error: Argumento faltante.\n");
        printf("Uso: %s\n", uso_msg);
        return 0;
    }
    return 1;
}
