# 📅 Historial de Cambios (Changelog)

El objetivo de este archivo es llevar un registro cronológico de las versiones, nuevas funcionalidades y correcciones de errores del sistema operativo.

## [v1.4.0] - 2026-02-18
### Añadido
- **Comando `eliminar`**: Permite eliminar archivos del sistema de archivos.
- **Función `cmd_eliminar()`**: Implementada en `file_commands.c` usando `remove()`.

### Cambios
- Actualizado `cmd_ayuda()` con información del nuevo comando.
- Actualizado README.md con 9 comandos funcionales.
- Integrado comando en el registro de comandos en `shell_loop.c`.

## [v1.3.0] - 2026-02-13
### Añadido
- **Sistema de UI con colores**: Códigos ANSI para mejorar la presentación visual.
- **Archivo `ui.h`**: Definiciones de colores y estilos ANSI.
- **Archivo `ui.c`**: Funciones helper de formato (banner, prompt, mensajes).
- **Separadores visuales**: Para estructurar mejor la salida de comandos.

### Cambios
- Actualizado `cmd_ayuda()` con formato mejorado y colores.
- Banner de bienvenida rediseñado con colores y separadores.
- Prompt del shell ahora en azul y negrita.
- Mensajes de error en rojo, éxitos en verde, info en cyan.
- Mejorado formato del comando `historial` con numeración en color.

## [v1.2.0] - 2026-02-12
### Añadido
- **Comando `crear`**: Crea archivos vacíos en el directorio actual.

### Cambios
- Integrado comando `crear` en el registro de comandos.
- Actualizada documentación del comando `ayuda`.

## [v1.1.0] - 2026-02-11
### Añadido
- **Comando `historial`**: Muestra los últimos 10 comandos ejecutados.
- **Sistema de buffer circular**: Implementación eficiente para el historial.
- **Archivo `advanced_commands.c`**: Módulo para comandos avanzados.

### Cambios
- Reordenados comandos en la tabla de registro alfabéticamente.
- Integración del historial en el bucle principal del shell.

## [v1.0.0] - 2026-02-04
### Añadido
- **Shell Interactiva**: Bucle REPL funcional.
- **Comandos Básicos**: `listar`, `leer`, `tiempo`, `calc`, `ayuda`, `salir`.
- **Arquitectura Modular**: Separación en `core`, `commands`, `utils`.
- **Sistema de Documentación**: Soporte para Doxygen.

### Cambios
- Migración de `main.c` monolítico a estructura modular.
