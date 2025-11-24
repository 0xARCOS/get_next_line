/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariarcos <ariarcos>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by tu_login          #+#    #+#             */
/*   Updated: 2025/11/24 11:58:33 by ariarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_handle_memory(char **acc_buffer, char *nl_ptr, size_t line_len)
{
	char	*old_ptr;
	size_t	residue_len;

	if (!nl_ptr)
	{
		free(*acc_buffer);
		*acc_buffer = NULL;
		return (1);
	}
	old_ptr = *acc_buffer;
	residue_len = ft_strlen(old_ptr) - line_len;
	if (residue_len > 0)
	{
		*acc_buffer = ft_substr(old_ptr, line_len, residue_len);
		if (!*acc_buffer)
			return (free(old_ptr), -1);
	}
	else
		*acc_buffer = NULL;
	free(old_ptr);
	return (1);
}

static char	*ft_extract_and_clean(char **acc_buffer)
{
	char	*nl_ptr;
	char	*line;
	size_t	line_len;
	int		status;

	if (!*acc_buffer)
		return (NULL);
	nl_ptr = ft_strchr(*acc_buffer, '\n');
	if (nl_ptr)
		line_len = (nl_ptr - *acc_buffer) + 1;
	else
		line_len = ft_strlen(*acc_buffer);
	if (line_len == 0)
		return (free(*acc_buffer), *acc_buffer = NULL, NULL);
	line = ft_substr(*acc_buffer, 0, line_len);
	if (!line)
		return (NULL);
	status = ft_handle_memory(acc_buffer, nl_ptr, line_len);
	if (status == -1)
		return (free(line), NULL);
	return (line);
}

static int	ft_read_data(int fd, char **acc_buffer)
{
	char	*buf;
	ssize_t	bytes_read;
	char	*temp;

	if (*acc_buffer && ft_strchr(*acc_buffer, '\n'))
		return (1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free(buf), -1);
	if (bytes_read == 0)
		return (free(buf), 0);
	buf[bytes_read] = '\0';
	temp = *acc_buffer;
	*acc_buffer = ft_strjoin(*acc_buffer, buf);
	free(buf);
	if (temp)
		free(temp);
	if (!*acc_buffer)
		return (-1);
	return (ft_read_data(fd, acc_buffer));
}

char	*get_next_line(int fd)
{
	static char	*residue_buffer[1024];
	char		*final_line;
	int			status;

	if (fd < 0 || fd >= 1024)
		return (NULL);
	status = ft_read_data(fd, &residue_buffer[fd]);
	if (status == -1 || (status == 0 && !residue_buffer[fd]))
	{
		if (residue_buffer[fd])
		{
			free(residue_buffer[fd]);
			residue_buffer[fd] = NULL;
		}
		return (NULL);
	}
	final_line = ft_extract_and_clean(&residue_buffer[fd]);
	return (final_line);
}

// int main(void)
// {
//     int fd;
//     char *line;
//     fd = open("file.txt", O_RDONLY);
//     // int fd2 = open("get_next_line.c", O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error al abrir el archivo");
//         return 1;
//     }
//     printf("%s\n", get_next_line(0));
//     close(fd);
//     return 0;
// }