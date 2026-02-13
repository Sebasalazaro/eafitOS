/**
 * @file ui.h
 * @brief Utilidades para la interfaz de usuario (colores y formato).
 * 
 * Define colores ANSI y funciones para mejorar la presentación visual
 * de la shell sin usar emojis ni caracteres especiales complejos.
 */

#ifndef UI_H
#define UI_H

// --- Códigos de Color ANSI ---
// Estos son secuencias de escape que la terminal interpreta como colores
// Formato: \x1b[CODIGOm donde CODIGO define el color/estilo

// Colores de texto
#define COLOR_ROJO     "\x1b[31m"
#define COLOR_VERDE    "\x1b[32m"
#define COLOR_AMARILLO "\x1b[33m"
#define COLOR_AZUL     "\x1b[34m"
#define COLOR_MAGENTA  "\x1b[35m"
#define COLOR_CYAN     "\x1b[36m"
#define COLOR_BLANCO   "\x1b[37m"

// Estilos
#define ESTILO_NEGRITA "\x1b[1m"
#define ESTILO_DIM     "\x1b[2m"

// Reset (volver a color normal)
#define COLOR_RESET    "\x1b[0m"

// --- Combinaciones Útiles ---
#define COLOR_ERROR    COLOR_ROJO ESTILO_NEGRITA
#define COLOR_EXITO    COLOR_VERDE
#define COLOR_INFO     COLOR_CYAN
#define COLOR_AVISO    COLOR_AMARILLO
#define COLOR_PROMPT   COLOR_AZUL ESTILO_NEGRITA

// --- Separadores ---
#define SEPARADOR_LARGO  "=========================================="
#define SEPARADOR_CORTO  "--------------------"

// --- Prototipos de Funciones ---

/**
 * @brief Imprime el banner de bienvenida con formato.
 */
void imprimir_banner(void);

/**
 * @brief Imprime un mensaje de error con formato (rojo).
 * @param mensaje Texto del error.
 */
void imprimir_error(const char *mensaje);

/**
 * @brief Imprime un mensaje de éxito con formato (verde).
 * @param mensaje Texto del éxito.
 */
void imprimir_exito(const char *mensaje);

/**
 * @brief Imprime un mensaje informativo con formato (cyan).
 * @param mensaje Texto informativo.
 */
void imprimir_info(const char *mensaje);

/**
 * @brief Imprime un separador visual.
 */
void imprimir_separador(void);

/**
 * @brief Imprime el prompt personalizado.
 */
void imprimir_prompt(void);

#endif
