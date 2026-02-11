# 📅 Historial de Cambios (Changelog)

El objetivo de este archivo es llevar un registro cronológico de las versiones, nuevas funcionalidades y correcciones de errores del sistema operativo.

## [v1.1.0] - 2026-02-11
### Añadido
- **Comando `historial`**: Muestra los últimos 10 comandos ejecutados.
- **Comando `crear`**: Crea archivos vacíos en el directorio actual.
- **Sistema de buffer circular**: Implementación eficiente para el historial.
- **Archivo `advanced_commands.c`**: Módulo para comandos avanzados.

### Cambios
- Actualizado `cmd_ayuda()` para incluir los nuevos comandos.
- Reordenados comandos en la tabla de registro alfabéticamente.

## [v1.0.0] - 2026-02-04
### Añadido
- **Shell Interactiva**: Bucle REPL funcional.
- **Comandos Básicos**: `listar`, `leer`, `tiempo`, `calc`, `ayuda`, `salir`.
- **Arquitectura Modular**: Separación en `core`, `commands`, `utils`.
- **Sistema de Documentación**: Soporte para Doxygen.

### Cambios
- Migración de `main.c` monolítico a estructura modular.
