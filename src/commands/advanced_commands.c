/**
 * @file advanced_commands.c
 * @brief Comandos avanzados del sistema.
 * 
 * Contiene comandos adicionales como historial, crear archivos, etc.
 */

#include <stdio.h>
#include <string.h> // Para strcpy, strlen
#include "commands.h"

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
    printf("--- Historial de Comandos ---\n");
    
    // Si no se han ejecutado comandos aún:
    if (contador_historial == 0) {
        printf("(El historial está vacío)\n");
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
        
        // Mostrar con numeración: 1. comando_mas_reciente, 2. anterior, etc.
        printf("%2d. %s\n", i + 1, historial[indice]);
    }
    
    (void)args;
}
