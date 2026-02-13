/**
 * @file ui.c
 * @brief Implementación de utilidades de interfaz.
 * 
 * Contiene funciones para mejorar la presentación visual de la shell,
 * usando colores ANSI y separadores.
 */

#include <stdio.h>
#include "ui.h"

/**
 * @brief Imprime el banner de bienvenida estilizado.
 * 
 * Se muestra al iniciar la shell con formato visual mejorado.
 * Usa colores y separadores para dar una apariencia profesional.
 */
void imprimir_banner(void) {
    printf("\n");
    printf(COLOR_CYAN ESTILO_NEGRITA);
    printf("%s\n", SEPARADOR_LARGO);
    printf("     EAFITos - Shell Educativa v1.1\n");
    printf("%s\n", SEPARADOR_LARGO);
    printf(COLOR_RESET);
    
    printf(COLOR_AMARILLO);
    printf("  Sistema operativo educativo para aprender C\n");
    printf(COLOR_RESET);
    
    printf(COLOR_DIM);
    printf("  Escribe 'ayuda' para ver los comandos\n");
    printf(COLOR_RESET);
    
    printf(COLOR_CYAN);
    printf("%s\n", SEPARADOR_LARGO);
    printf(COLOR_RESET);
    printf("\n");
}

/**
 * @brief Imprime un mensaje de error con formato.
 * 
 * Los errores se muestran en rojo y negrita para destacar.
 * 
 * @param mensaje Cadena con el texto del error.
 */
void imprimir_error(const char *mensaje) {
    printf(COLOR_ERROR "[ERROR] %s" COLOR_RESET "\n", mensaje);
}

/**
 * @brief Imprime un mensaje de éxito con formato.
 * 
 * Los mensajes de éxito se muestran en verde para indicar
 * que la operación se completó correctamente.
 * 
 * @param mensaje Cadena con el texto del éxito.
 */
void imprimir_exito(const char *mensaje) {
    printf(COLOR_EXITO "[OK] %s" COLOR_RESET "\n", mensaje);
}

/**
 * @brief Imprime un mensaje informativo con formato.
 * 
 * La información general se muestra en cyan para distinguirla
 * de errores y éxitos.
 * 
 * @param mensaje Cadena con el texto informativo.
 */
void imprimir_info(const char *mensaje) {
    printf(COLOR_INFO "[INFO] %s" COLOR_RESET "\n", mensaje);
}

/**
 * @brief Imprime un separador visual.
 * 
 * Útil para dividir secciones de salida y mejorar la legibilidad.
 */
void imprimir_separador(void) {
    printf(COLOR_DIM "%s" COLOR_RESET "\n", SEPARADOR_CORTO);
}

/**
 * @brief Imprime el prompt de la shell con formato.
 * 
 * El prompt se muestra en azul negrita para distinguirlo claramente
 * de la salida de los comandos.
 */
void imprimir_prompt(void) {
    printf(COLOR_PROMPT "EAFITos> " COLOR_RESET);
    fflush(stdout); // Asegurar que se imprima inmediatamente
}
