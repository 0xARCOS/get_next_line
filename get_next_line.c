#include "get_next_line.h"

int ft_manejar_memoria(char **buffer_acumulado, char *nl_ptr, size_t line_len)
{
    char    *p_old;
    size_t  len_residuo;

    if (!nl_ptr) // Caso: No se encontró '\n' (Fin de archivo)
    {
        free(*buffer_acumulado);
        *buffer_acumulado = NULL;
        return (1);
    }
    p_old = *buffer_acumulado;
    len_residuo = ft_strlen(p_old) - line_len;
    if (len_residuo > 0)
    {
        *buffer_acumulado = ft_substr(p_old, line_len, len_residuo);
        if (!buffer_acumulado)
        {
            free(p_old);
            return (-1);
        }
    }
    else
        *buffer_acumulado = NULL;
    free(p_old);
    return (1);
}

char *ft_extraer_y_limpiar(char **buffer_acumulado)
{
    char *nl_ptr;
    char *line;
    size_t line_len;
    int status;

    if (!*buffer_acumulado)
        return (NULL);
    nl_ptr = ft_strchr(*buffer_acumulado, '\n'); 
    if (nl_ptr)
        line_len = (nl_ptr - *buffer_acumulado) + 1;
    else
        line_len = ft_strlen(*buffer_acumulado);
    if (line_len == 0) 
    { 
        free(*buffer_acumulado);
        *buffer_acumulado = NULL; 
        return (NULL);
    }
    line = ft_substr(*buffer_acumulado, 0, line_len); 
    if (!line) 
        return (NULL); 
    status = ft_manejar_memoria(buffer_acumulado, nl_ptr, line_len);
    if (status == -1)
        return (free(line), NULL);
    return (line);
}

int ft_leer_datos(int fd, char **buffer_acumulado)
{
    char buf[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    char    *temp;
    char    *nl;

    if (*buffer_acumulado && ft_strchr(*buffer_acumulado, '\n'))
        return (1);
    bytes_read = read(fd, buf, BUFFER_SIZE);
    if (bytes_read == -1) 
        return (-1);
    if (bytes_read == 0) 
        return (0);
    buf[bytes_read] = '\0';
    temp = *buffer_acumulado;
    *buffer_acumulado = ft_strjoin(*buffer_acumulado, buf);
 
    if (temp)
        free (temp);
    if (*buffer_acumulado == NULL)
        return (-1);

    nl = ft_strchr(*buffer_acumulado, '\n');
    if (nl) 
        return (1);
    return (ft_leer_datos(fd, buffer_acumulado));
}

char *get_next_line(int fd)
{
    static char *buffer_residuo[1024];
    char *final_line;
    int estado;

    if (fd < 0 || fd >= 1024)
        return NULL;
    
    // Llamamos a la función auxiliar ft_leer_datos
    estado = ft_leer_datos(fd, &buffer_residuo[fd]);
    if (estado == -1 || (estado == 0 && !buffer_residuo[fd]))
    {
        if (buffer_residuo[fd])
            free(buffer_residuo[fd]);
        return NULL;
    }

    final_line = ft_extraer_y_limpiar(&buffer_residuo[fd]);

    return (final_line);
}

int main(void)
{
    int fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}