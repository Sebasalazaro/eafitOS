/**
 * @file commands.h
 * @brief Interfaz para los comandos del sistema.
 * 
 * Define las funciones que implementan la lógica de cada comando disponible
 * en la shell. Todas siguen la firma `void cmd_nombre(char **args)`.
 */

#ifndef COMMANDS_H
#define COMMANDS_H

// --- Prototipos de Comandos ---

// File Commands
/**
 * @brief Lista los archivos del directorio actual.
 */
void cmd_list(char **args);

/**
 * @brief Lee y muestra el contenido de un archivo.
 */
void cmd_read(char **args);

/**
 * @brief Crea un archivo vacío.
 */
void cmd_create(char **args);

/**
 * @brief Elimina un archivo del sistema.
 */
void cmd_remove(char **args);

/**
 * @brief Muestra información detallada de un archivo (tamaño, fechas, permisos).
 */
void cmd_stats(char **args);

// System Commands
/**
 * @brief Muestra la hora del sistema.
 */
void cmd_time(char **args);

/**
 * @brief Realiza operaciones matemáticas simples.
 */
void cmd_calc(char **args);

/**
 * @brief Muestra el historial de comandos ejecutados.
 */
void cmd_history(char **args);

// Basic Commands
/**
 * @brief Muestra la lista de ayuda.
 */
void cmd_help(char **args);

/**
 * @brief Termina la ejecución de la shell.
 */
void cmd_exit(char **args);

// --- Utilidades del Registro de Comandos ---

/**
 * @brief Agrega un comando al historial.
 * @param comando Cadena con el comando a guardar.
 */
void agregar_al_historial(const char *comando);

/**
 * @brief Retorna el número total de comandos registrados.
 * @return int Cantidad de comandos.
 */
int num_comandos();

#endif
