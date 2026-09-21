/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amigdadi <amigdadi@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:54:31 by amigdadi          #+#    #+#             */
/*   Updated: 2026/01/12 14:27:05 by amigdadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*extract_line(const char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i-- > 0)
		line[i] = stash[i];
	return (line);
}

char	*save_rest(const char *stash)
{
	size_t	i;
	size_t	j;
	char	*rest;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] != '\n' || !stash[i + 1])
		return (NULL);
	rest = (char *)malloc(ft_strlen(stash + i + 1) + 1);
	if (!rest)
		return (NULL);
	j = 0;
	while (stash[i + 1 + j])
	{
		rest[j] = stash[i + 1 + j];
		j++;
	}
	rest[j] = '\0';
	return (rest);
}
