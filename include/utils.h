/**
 * @file utils.h
 * @brief Funciones auxiliares y utilidades del sistema.
 * 
 * Contiene prototipos de funciones helper reutilizables que son utilizadas
 * por múltiples comandos del sistema.
 */

#ifndef UTILS_H
#define UTILS_H

#include <time.h>  // Para time_t
#include <stddef.h> // Para size_t

// --- Funciones de Formateo ---

/**
 * @brief Formatea un tamaño en bytes a una representación legible (bytes/KB/MB/GB).
 */
void formatear_tamano(double bytes, char *buffer, size_t size);

/**
 * @brief Formatea un timestamp UNIX a formato dd/mm/yyyy hh:mm:ss.
 */
void formatear_fecha(time_t timestamp, char *buffer, size_t size);

// --- Funciones de Validación ---

/**
 * @brief Verifica si un archivo existe usando stat().
 * @return 1 si existe, 0 si no.
 */
int archivo_existe(const char *ruta);

/**
 * @brief Valida que un argumento específico no sea NULL.
 * @return 1 si es válido, 0 si es NULL (e imprime mensaje de error).
 */
int validar_argumento(char **args, int indice, const char *uso_msg);

#endif
