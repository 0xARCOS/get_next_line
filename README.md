<div align="center">
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/get_next_line-light.png#gh-light-mode-only" alt="Banner claro" />
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/get_next_line-dark.png#gh-dark-mode-only" alt="Banner oscuro" />
    <a href='https://profile.intra.42.fr/users/aarcos' target="_blank">
        <img alt='Campus 42 Madrid' src='https://img.shields.io/badge/Madrid-black?style=flat&logo=42&logoColor=white'/>
    </a>
    <img src="https://img.shields.io/badge/puntuación-💯%2F100-success?color=%2312bab9&style=flat" />
    <img src="https://api.visitorbadge.io/api/visitors?user=0xARCOS&repo=get_next_line&label=visitas&countColor=%2385e3ff&style=flat&labelStyle=none"/>
</div>

---

# get_next_line

> Leer una línea de un descriptor de archivo puede parecer trivial, pero ¿y si sólo puedes usar `read()` una vez por llamada? Este proyecto entrena memoria dinámica, buffers y control de archivos.

---

## 📦 Descripción

`get_next_line` es una función que devuelve una línea leída desde un descriptor de archivo (fd), sin importar su tamaño. Es parte del currículum de la **42 School** y una base sólida para proyectos que trabajan con archivos, sockets o entradas estándar.

---

## 📁 Estructura del Proyecto

```
get_next_line/
├── get_next_line.h        # Declaraciones
├── get_next_line.c        # Funciones principales
├── get_next_line_utils.c  # Funciones auxiliares
```

---

## ⚙️ Compilación

Puedes compilar los archivos con:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

O usando un `Makefile`:

```bash
make
```

---

## 🧠 Uso

```c
char *line;
int fd = open("archivo.txt", O_RDONLY);
line = get_next_line(fd);
printf("%s", line);
```

La función devuelve:
- Una línea completa (terminada en `\n` si hay una)
- `NULL` al llegar al EOF o en caso de error

---

## 💡 Ejemplo de Salida

Archivo de entrada:
```
Hola mundo
Esto es una prueba
```

Output esperado:
```
Hola mundo
Esto es una prueba
```

---

## 🧰 Funciones principales

### `char *get_next_line(int fd);`
Lee una línea del archivo, manejando buffer estático para mantener datos entre llamadas.

### `BUFFER_SIZE`
Tamaño del buffer usado en cada llamada a `read()`. Puede modificarse en la compilación con `-D`.

---

## 🧑‍💻 Autor

**Ariel (0xARCOS)**  
📍 Campus 42 Madrid  
🔗 [GitHub](https://github.com/0xARCOS)

---

## 📜 Licencia

Este proyecto es parte del aprendizaje en 42 y puede ser reutilizado para fines educativos.

