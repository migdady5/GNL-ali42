#include "get_next_line.h"

static char	*gnl_cleanup(char **stash)
{
	free(*stash);
	*stash = NULL;
	return (NULL);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;

	bytes = 1;
	while (bytes > 0 && !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes] = '\0';
		if (bytes > 0)
		{
			stash = ft_strjoin(stash, buffer);
			if (!stash)
				return (NULL);
		}
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash || stash[0] == '\0')
		return (gnl_cleanup(&stash));
	line = extract_line(stash);
	if (!line)
		return (gnl_cleanup(&stash));
	rest = save_rest(stash);
	free(stash);
	stash = rest;
	return (line);
}
