/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariarcos <ariarcos>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:58:01 by ariarcos          #+#    #+#             */
/*   Updated: 2025/11/24 11:58:52 by ariarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char *get_next_line(int fd);

int ft_strlen(const char *s);
char *ft_strjoin(const char *s1, const char *s2);
char *ft_strchr(const char *s, int c);
char *ft_substr(const char *s, unsigned int start, size_t len);


#endif 