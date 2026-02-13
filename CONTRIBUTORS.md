# Colaboradores del Proyecto

Este archivo reconoce a las personas que han contribuido al desarrollo de **EAFITos**.

## Desarrollador Principal

**Sebastián Salazar Osorio**
- Arquitectura del sistema y diseño modular
- Implementación del núcleo (shell loop, parser)
- Desarrollo de todos los comandos (básicos y avanzados)
- Sistema de historial con buffer circular
- Sistema de UI con colores ANSI
- Documentación técnica y guías de usuario
- Testing y depuración

## Contribuciones por Módulo

### Core (`src/core/`)
- **main.c**: Punto de entrada y banner de bienvenida
- **shell_loop.c**: REPL, registro de comandos e integración del historial
- **parser.c**: Lectura y parsing de entrada de usuario

### Comandos (`src/commands/`)
- **basic_commands.c**: ayuda, salir, tiempo
- **file_commands.c**: listar, leer
- **system_commands.c**: calc
- **advanced_commands.c**: historial, crear

### Utilidades (`src/utils/`)
- **ui.c**: Sistema de colores y formato con ANSI
- **helpers.c**: Funciones auxiliares compartidas
- **error_handler.c**: Manejo de errores
- **memory_manager.c**: Gestión de memoria

## Estadísticas del Proyecto

- **Líneas de código**: ~1000+ líneas
- **Archivos fuente**: 11 archivos .c
- **Comandos implementados**: 8
- **Tiempo de desarrollo**: Febrero 2026
- **Repositorio**: GitHub

## Agradecimientos

- **Universidad EAFIT** por el curso de Sistemas Operativos
- **Profesor**: Edison Valencia
- **Documentación de referencia**: GNU C Library, Linux man pages

---

*Este es un proyecto académico individual desarrollado como parte del curso de Sistemas Operativos en EAFIT.*
