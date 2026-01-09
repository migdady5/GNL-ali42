#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
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

static void	ft_copy(char *dst, const char *src, size_t *i)
{
	size_t	j;

	if (!src)
		return ;
	j = 0;
	while (src[j])
	{
		dst[*i] = src[j];
		(*i)++;
		j++;
	}
}

char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(len + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	ft_copy(res, s1, &i);
	ft_copy(res, s2, &i);
	res[i] = '\0';
	free(s1);
	return (res);
}

static char	*ft_subdup(const char *s, size_t start)
{
	size_t	len;
	size_t	i;
	char	*res;

	if (!s || s[start] == '\0')
		return (NULL);
	len = ft_strlen(s + start);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*extract_line(const char *stash)
{
	size_t	len;
	size_t	i;
	char	*line;

	if (!stash || stash[0] == '\0')
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*save_rest(const char *stash)
{
	size_t	i;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] != '\n')
		return (NULL);
	return (ft_subdup(stash, i + 1));
}
