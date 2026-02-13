/**
 * @file basic_commands.c
 * @brief Implementación de comandos básicos del sistema.
 */

#include <stdio.h>  // printf
#include <stdlib.h> // exit, malloc
#include <time.h>   // time, localtime, strftime
#include "commands.h"
#include "ui.h"     // Colores y formato

/**
 * @brief Comando AYUDA
 * 
 * Muestra al usuario la lista de acciones que puede realizar.
 * Es fundamental para la usabilidad de la shell.
 * 
 * @param args Argumentos del comando (no se usan aquí, por eso (void)args).
 */
void cmd_ayuda(char **args) {
    printf("\n");
    printf(COLOR_CYAN ESTILO_NEGRITA "=== Ayuda de EAFITos ===" COLOR_RESET "\n\n");
    
    printf(COLOR_AMARILLO "Comandos disponibles:\n" COLOR_RESET);
    printf(COLOR_DIM "%s\n" COLOR_RESET, SEPARADOR_LARGO);
    
    printf(COLOR_VERDE "  listar" COLOR_RESET "\n");
    printf("    Muestra archivos del directorio actual\n\n");
    
    printf(COLOR_VERDE "  leer <archivo>" COLOR_RESET "\n");
    printf("    Muestra el contenido de un archivo\n\n");
    
    printf(COLOR_VERDE "  crear <archivo>" COLOR_RESET "\n");
    printf("    Crea un archivo vacío\n\n");
    
    printf(COLOR_VERDE "  tiempo" COLOR_RESET "\n");
    printf("    Muestra la fecha y hora actual\n\n");
    
    printf(COLOR_VERDE "  calc <n1> <op> <n2>" COLOR_RESET "\n");
    printf("    Realiza cálculos simples (+, -, *, /)\n");
    printf("    Ejemplo: calc 10 + 5\n\n");
    
    printf(COLOR_VERDE "  historial" COLOR_RESET "\n");
    printf("    Muestra los últimos 10 comandos ejecutados\n\n");
    
    printf(COLOR_VERDE "  ayuda" COLOR_RESET "\n");
    printf("    Muestra este mensaje\n\n");
    
    printf(COLOR_VERDE "  salir" COLOR_RESET "\n");
    printf("    Termina la sesión\n\n");
    
    printf(COLOR_DIM "%s\n" COLOR_RESET, SEPARADOR_LARGO);
    
    (void)args;
}

/**
 * @brief Comando SALIR
 * 
 * Finaliza la ejecución del programa de forma controlada.
 * Utiliza la llamada al sistema exit().
 * 
 * @param args Argumentos del comando (ignorados).
 */
void cmd_salir(char **args) {
    printf("Saliendo de la shell...\n");
    // exit(0) devuelve el código 0 al sistema operativo padre,
    // indicando que el proceso terminó sin errores.
    exit(0);
    (void)args;
}

/**
 * @brief Comando TIEMPO (date)
 * 
 * Obtiene y formatea la fecha y hora del sistema.
 * Demuestra el uso de la librería estándar <time.h>.
 * 
 * @param args Argumentos del comando (ignorados).
 */
void cmd_tiempo(char **args) {
    // 1. Obtener tiempo "crudo" (segundos desde 1970 - Epoch Unix)
    time_t t = time(NULL);
    
    // 2. Convertir a una estructura estructurada local (struct tm)
    // localtime devuelve un puntero, así que desreferenciamos con *
    struct tm tm = *localtime(&t);
    
    // 3. Imprimir con formato
    // tm_year cuenta desde 1900, por eso sumamos 1900.
    // tm_mon es 0-11, por eso sumamos 1.
    printf("Fecha y Hora del Sistema: %02d-%02d-%04d %02d:%02d:%02d\n",
           tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
           tm.tm_hour, tm.tm_min, tm.tm_sec);
           
    (void)args;
}
