#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//#  define BUFFER_SIZE 42

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char *get_next_line(int fd);
char *ft_extraer_y_limpiar(char **buffer_acumulado);
int ft_leer_datos(int fd, char **buffer_acumulado);

int ft_strlen(const char *s);
char *ft_strjoin(const char *s1, const char *s2);
char *ft_strchr(const char *s, int c);
char *ft_substr(const char *s, unsigned int start, size_t len);


#endif 