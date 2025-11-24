/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariarcos <ariarcos>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:48:53 by ariarcos          #+#    #+#             */
/*   Updated: 2025/11/24 14:49:01 by ariarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *s)
{
	ssize_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	len1;

	i = 0;
	j = 0;
	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	ptr = (char *)malloc(len1 + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			ptr[i] = s1[i];
			i++;
		}
	}
	while (s2 && s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	char			*str;
	size_t			i;

	s_len = ft_strlen(s);
	str = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	if (start >= s_len || !*s)
		return (NULL);
	if (len > s_len - start)
		len = s_len - start;
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
