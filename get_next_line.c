/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariarcos <ariarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 05:14:23 by ariarcos          #+#    #+#             */
/*   Updated: 2025/11/12 19:51:23 by ariarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_manejar_memoria(char **buffer_acumulado, char *nl_ptr, size_t line_len)
{
	char	*p_old;
	size_t	len_residuo;

	if (!nl_ptr)
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
		if (!*buffer_acumulado)
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

char	*ft_extraer_y_limpiar(char **buffer_acumulado)
{
	char	*nl_ptr;
	char	*line;
	size_t	line_len;
	int		status;

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

static int	ft_error(char **buffer_acumulado, char *buf)
{
	free(buf);
	if (*buffer_acumulado)
	{
		free(*buffer_acumulado);
		*buffer_acumulado = NULL;
	}
	return (-1);
}

int	ft_leer_datos(int fd, char **buffer_acumulado)
{
	char		*buf;
	ssize_t		bytes_read;
	char		*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	while (!(*buffer_acumulado && ft_strchr(*buffer_acumulado, '\n')))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_error(buffer_acumulado, buf));
		if (bytes_read == 0)
			return (free(buf), 0);
		buf[bytes_read] = '\0';
		temp = *buffer_acumulado;
		*buffer_acumulado = ft_strjoin(*buffer_acumulado, buf);
		free(temp);
		if (!*buffer_acumulado)
			return (free(buf), -1);
	}
	return (free(buf), 1);
}

char	*get_next_line(int fd)
{
	static char	*buffer_residuo[1024];
	char		*final_line;
	int			estado;

	if (fd < 0 || fd >= 1024)
		return (NULL);
	estado = ft_leer_datos(fd, &buffer_residuo[fd]);
	if (estado == -1)
	{
		free(buffer_residuo[fd]);
		buffer_residuo[fd] = NULL;
		return (NULL);
	}
	if (estado == 0 && !buffer_residuo[fd])
		return (NULL);
	final_line = ft_extraer_y_limpiar(&buffer_residuo[fd]);
	return (final_line);
}
