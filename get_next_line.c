/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amigdadi <amigdadi@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:44:04 by amigdadi          #+#    #+#             */
/*   Updated: 2026/01/12 14:44:11 by amigdadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*stash_free(t_stash *st)
{
	free(st->s);
	st->s = NULL;
	st->len = 0;
	st->cap = 0;
	return (NULL);
}

static int	stash_reserve(t_stash *st, size_t need)
{
	char	*newbuf;
	size_t	newcap;
	size_t	i;

	if (need <= st->cap)
		return (1);
	newcap = st->cap;
	if (newcap == 0)
		newcap = 1024;
	while (newcap < need)
		newcap *= 2;
	newbuf = (char *)malloc(newcap);
	if (!newbuf)
		return (0);
	i = 0;
	while (i < st->len)
	{
		newbuf[i] = st->s[i];
		i++;
	}
	free(st->s);
	st->s = newbuf;
	st->cap = newcap;
	return (1);
}

static int	stash_append(t_stash *st, const char *buf, ssize_t n)
{
	size_t	i;

	if (n <= 0)
		return (1);
	if (!stash_reserve(st, st->len + (size_t)n + 1))
		return (0);
	i = 0;
	while (i < (size_t)n)
	{
		st->s[st->len + i] = buf[i];
		i++;
	}
	st->len += (size_t)n;
	st->s[st->len] = '\0';
	return (1);
}

static char	*read_to_stash(int fd, t_stash *st)
{
	char	*buf;
	ssize_t	bytes;

	buf = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buf), NULL);
		buf[bytes] = '\0';
		if (!stash_append(st, buf, bytes))
			return (free(buf), NULL);
		if (ft_strchr(buf, '\n') || bytes == 0)
			break ;
	}
	free(buf);
	return (st->s);
}

char	*get_next_line(int fd)
{
	static t_stash	st;
	char			*line;
	char			*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_to_stash(fd, &st))
		return (stash_free(&st));
	if (!st.s || st.len == 0)
		return (stash_free(&st));
	line = extract_line(st.s);
	if (!line)
		return (stash_free(&st));
	rest = save_rest(st.s);
	free(st.s);
	st.s = rest;
	st.len = ft_strlen(st.s);
	st.cap = st.len + 1;
	return (line);
}
