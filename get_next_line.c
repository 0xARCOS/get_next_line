/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 02:14:41 by aarcos            #+#    #+#             */
/*   Updated: 2025/01/31 13:02:55 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line2(char *remainder)
{
	char	*line;
	int		i;

	i = 0;
	if (!remainder)
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_remainder(char *remainder)
{
	char	*new_remainder;
	char	*newline_pos;

	newline_pos = ft_strchr(remainder, '\n');
	if (!newline_pos || !newline_pos[1])
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = ft_strjoin(newline_pos + 1, "");
	free(remainder);
	return (new_remainder);
}

int	read_to_remainder(char **remainder, int fd, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	while (!ft_strchr(*remainder, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(*remainder), 1);
		if (bytes_read == 0)
			return (0);
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(*remainder, buffer);
		free(*remainder);
		*remainder = tmp;
		if (!tmp)
			return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_to_remainder(&remainder, fd, buffer) && !remainder)
		return (NULL);
	if (!remainder)
		return (NULL);
	line = get_line2(remainder);
	if (!line)
		return (NULL);
	remainder = update_remainder(remainder);
	return (line);
}
