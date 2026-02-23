# Colaboradores del Proyecto

Este archivo reconoce a las personas que han contribuido al desarrollo de **EAFITos**.

## Desarrollador Principal

**Sebastián Salazar Osorio**
- Arquitectura del sistema y diseño modular (principios SOLID)
- Implementación del núcleo (shell loop, parser)
- Desarrollo de todos los comandos con sintaxis Unix-like
- Sistema de historial con buffer circular (aritmética modular)
- Sistema de UI con colores ANSI y separadores visuales
- Funciones helper reutilizables (DRY principle)
- Confirmaciones de seguridad en operaciones destructivas
- Refactorización completa de nomenclatura (español → inglés)
- Documentación técnica completa (README, CHANGELOG)
- Testing y depuración en WSL/Linux

## Contribuciones por Módulo

### Core (`src/core/`)
- **main.c**: Punto de entrada y banner de bienvenida
- **shell_loop.c**: REPL, registro de comandos e integración del historial
- **parser.c**: Lectura y parsing de entrada de usuario

### Comandos (`src/commands/`)
- **basic_commands.c**: help, exit, time
- **file_commands.c**: list, read
- **system_commands.c**: calc
- **advanced_commands.c**: history, create, remove, stats

### Utilidades (`src/utils/`)
- **ui.c**: Sistema de colores y formato con ANSI (banner, prompt, mensajes)
- **helpers.c**: Funciones auxiliares reutilizables (formateo, validación)
- **error_handler.c**: Manejo de errores (placeholder para expansión)
- **memory_manager.c**: Gestión de memoria (placeholder para expansión)

## Estadísticas del Proyecto

- **Líneas de código**: ~1500+ líneas (C puro)
- **Archivos fuente**: 11 archivos .c + 4 headers
- **Comandos implementados**: 10 comandos funcionales con sintaxis Unix-like
- **Funciones helper**: 4 funciones reutilizables en utils.h
- **Tiempo de desarrollo**: Febrero 2026 (11-23)
- **Repositorio**: GitHub (privado - proyecto académico)

## Agradecimientos

- **Universidad EAFIT** por el curso de Sistemas Operativos y las facilidades para el desarrollo
- **Profesor Edison Valencia** por la orientación técnica y los desafíos propuestos
- **Documentación de referencia**: 
  - GNU C Library Reference Manual
  - Linux man pages (opendir, stat, etc.)
  - POSIX.1-2017 Standard
- **Herramientas utilizadas**:
  - GCC Compiler
  - GNU Make
  - WSL (Windows Subsystem for Linux) para testing

---

*Este es un proyecto académico individual desarrollado como parte del curso de Sistemas Operativos en EAFIT.*  
*Demuestra comprensión de programación de sistemas, arquitectura modular, y uso de syscalls POSIX.*
