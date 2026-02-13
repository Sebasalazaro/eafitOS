# eafitOS

<div align="center">

Un sistema operativo educativo con shell interactiva desarrollado en C para explorar los fundamentos de programación de sistemas, gestión de procesos y estructuras de datos.

<br/>

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white) ![Make](https://img.shields.io/badge/Make-427819?style=for-the-badge&logo=gnu&logoColor=white) ![GCC](https://img.shields.io/badge/GCC-5C6BC0?style=for-the-badge&logo=gnu&logoColor=white) ![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black) ![Doxygen](https://img.shields.io/badge/Doxygen-2C4AA8?style=for-the-badge&logo=doxygen&logoColor=white)

</div>

---

## Descripción del Proyecto

EAFITos es un proyecto académico que implementa una shell interactiva (REPL) con comandos personalizados para gestión de archivos, cálculos matemáticos, historial de comandos y más. El sistema está diseñado siguiendo principios de programación modular en C, con una arquitectura clara que separa las responsabilidades en distintos módulos.

### Alcance Implementado

- ✅ **Shell interactiva** con bucle REPL (Read-Eval-Print-Loop)
- ✅ **8 comandos funcionales** incluyendo gestión de archivos, cálculos y utilidades
- ✅ **Sistema de historial** con buffer circular para últimos 10 comandos
- ✅ **Interfaz de usuario mejorada** con códigos ANSI para colores y formato
- ✅ **Arquitectura modular** separando core, comandos y utilidades
- ✅ **Documentación completa** con Doxygen y guías de usuario

## Comandos Disponibles

| Comando | Argumentos | Descripción | Ejemplo |
| :--- | :--- | :--- | :--- |
| `listar` | Ninguno | Muestra los archivos del directorio actual. | `listar` |
| `leer` | `<archivo>` | Muestra el contenido de un archivo de texto. | `leer README.md` |
| `crear` | `<archivo>` | Crea un archivo vacío. | `crear test.txt` |
| `tiempo` | Ninguno | Muestra la fecha y hora actual del sistema. | `tiempo` |
| `calc` | `<n1> <op> <n2>` | Realiza operaciones aritméticas (+, -, *, /). | `calc 10 * 2.5` |
| `historial` | Ninguno | Muestra los últimos 10 comandos ejecutados. | `historial` |
| `ayuda` | Ninguno | Muestra la lista de comandos disponibles con formato. | `ayuda` |
| `salir` | Ninguno | Termina la sesión de EAFITos. | `salir` |


## Características Técnicas

### Sistema de Registro de Comandos

El proyecto utiliza un sistema basado en arreglos de punteros a función para registrar y ejecutar comandos dinámicamente. Cada comando se implementa como una función `void cmd_nombre(char **args)` y se registra en `shell_loop.c`.

### Buffer Circular para Historial

El comando `historial` utiliza una implementación eficiente de buffer circular que mantiene los últimos 10 comandos sin necesidad de desplazar elementos en memoria. Usa aritmética modular para reescribir posiciones antiguas.

### Sistema de UI con Colores ANSI

El módulo `ui.c` proporciona funciones helper para imprimir mensajes con colores:
- **Errores** en rojo
- **Éxitos** en verde
- **Información** en cyan
- **Prompt** en azul con negrita
- **Separadores** para organizar visualmente la salida


## Inicio Rápido

### Compilación

Limpiar la build pasada
```bash
make clean
```

Crear nueva build
```bash
make
```

### Ejecución

```bash
make run
# O directamente:
./build/sistema_os
```

### Limpieza de Archivos de Compilación

```bash
make clean
```

## Estructura del Proyecto

```
eafitOS/
├── src/
│   ├── core/               # Núcleo del sistema
│   │   ├── main.c          # Punto de entrada
│   │   ├── shell_loop.c    # REPL y registro de comandos
│   │   └── parser.c        # Lectura y parsing de entrada
│   ├── commands/           # Implementación de comandos
│   │   ├── basic_commands.c
│   │   ├── file_commands.c
│   │   ├── system_commands.c
│   │   └── advanced_commands.c
│   └── utils/              # Utilidades compartidas
│       ├── helpers.c
│       ├── error_handler.c
│       ├── memory_manager.c
│       └── ui.c            # Sistema de colores y formato
├── include/                # Archivos de cabecera (.h)
├── build/                  # Archivos compilados
├── docs/                   # Documentación adicional
└── tests/                  # Pruebas unitarias e integración
```



## Documentación

Para generar la documentación técnica con Doxygen:

```bash
doxygen Doxyfile
```

Luego abre `docs/html/index.html` en tu navegador.

## Equipo de Desarrollo

- **Sebastian Salazar Osorio** - Desarrollo principal y arquitectura

## Notas de Desarrollo

- El proyecto está optimizado para compilación en Linux/WSL con GCC
- Se utiliza aritmética modular en el historial para eficiencia
- La función `(void)variable;` se usa para suprimir warnings de variables no utilizadas
- Todos los comentarios siguen formato Doxygen: `/** @brief Descripción */`

## Licencia

Este proyecto es de código abierto bajo la licencia MIT. Ver archivo `LICENSE` para más detalles.

---

**Curso**: Sistemas Operativos  
**Universidad**: EAFIT  
**Fecha**: Febrero 2026
