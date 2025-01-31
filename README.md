

## Estructura del proyecto

El proyecto se divide en tres archivos principales:
- get_next_line.h : Header con declaraciones.
- get_next_line.c : Funciones principales.
- get_next_line_utils.c : Funciones auxiliares

### get_next_line.h (Declaraciones)

``#ifndef GET_NEXT_LINE_H
``# define GET_NEXT_LINE_H

- Este es un guard header que previene inclusiones múltiples
- BUFFER_SIZE se define como 42 por defecto, pero puede cambiarse en la compilación


## Funciones Principales (get_next_line)
#### 1. get_next_line

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static char *remainder;
    char *line;
}

- 'static buffer' : Mantiene el buffer entre llamadas
- 'static remainder' : Guarda el contenido restante entre llamadas
- 'fd' : File descriptor del archivo a leer

#### 2. get_line2

char *get_line2(char *remainder)
{
    char *line;
    int i = 0;
}

- Extrae una línea del remainder hasta encontrar '\n'
- Cuenta caracteres hasta '\n' para asignar memoria
- Copia los caracteres a la nueva línea

#### 3. update_remainder

char *update_remainder(char *remainder)
{
    char *new_remainder;
    char *newline_pos;
}

- Actualiza el remainder después de extraer una línea
- Busca la posición '\n'
- Guardar el contenido después del '\n'

#### 4. read_to_remainder

int read_to_remainder(char **remainder, int fd, char *buffer)
{
    ssize_t bytes_read;
    char *tmp;
}

- Lee del archivo al buffer
- Une el buffer con remainder existente
- Continúa hasta encontrar '\n'

## Funciones Auxiliares (get_next_line_utils.c)

#### 1. ft_strlen

``size-t ft_strlen(char *str)
- Cuenta caracteres hasta '\0'
- Necesaria para gestionar string

#### 2. ft_strchr

``char *ft_strchr(char *s, int c)
- Busca primera ocurencia de un caracter
- Retorna puntero a la posición o NULL
- Crrucial  para encontrar '\n'

#### 3. ft_strjoin
`` char *ft_strjoin(char *s1, char *s2)
- Une dos strings en una nueva
- Gestiona casos donde s1 ees NULL
- Asigna memoria dinámicamente

## Flujo de Ejecución

##### 1. Entrada de Datos:
- La función recibe un fd
- Lee datos del archivo en bloques usando BUFFER_SIZE
- El fujo de entrada envía datos desde el archivo al pprograma
##### 2. Procesamiento
- Lee línea por línea hasta encontrar un carácter '\n'
- Almacena el contenido en un buffer temporal
- Procesa datos secuencialmente
- Si ecuentra una línea vacía, devuelve una string vacía
##### 3. Control de flujo
- Verifica si hay más contenido para leer
- Maneja el final del archivo (EOF)
- Gestiona errores y excepciones durante la lectura
##### 4. Salida
- Devuelve una línea completa terminada en null
- Mantiene el estado para la siguiente llamada
- Conserva el contenido restantee para futuras lecturas

## Gestión de Memoria

#### Asignación de Memoria
##### 1. Buffer Estático:
- Se utiliza un buffer estático para almacenar la lectura temporal
- El tamaño viene determinado por BUFFER_SIZE
- No requiere liberación manual
##### 2. Remainder
- Variable estática que mantiene el contenido entre llamadas
- debe liberarse correctamente cuando:
	- Se actualiza con nuevo contenido
	- Se llega al final del archivo
	- Ocurre un error

##### 3. Línea Retornada
- Se asigna memoria dinámicamente con malloc
- El tamaño se calcula hasta encontrar '\n' o '\0'
- La responsabilidad de liberar esta memoria es del llamador

#### Puntos Críticos
##### 1. Liberación de Memoria
- Liberar remainder antes de asignar nuevo contenido
- Evitar pérdidas de punteros een strjoin
- Manejar correctamente los casos de error

##### 2. Memory Leaks Comunes
- No liberar memoria al llegar a EOF
- Liberar memoria antes de retornar NULL
- No liberar memoria en casos de error

##### 3. Gestión de Errores
- Verificar retornos de malloc
- Liberar meemoria antes de retornar NULL
- Manejar errores de lectura correctamente

