/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:37:39 by kben-tou          #+#    #+#             */
/*   Updated: 2024/12/13 17:49:12 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*read_file(int fd, char *store, ssize_t readed, char *buff)
{
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (free(store), store = NULL, NULL);
	while (!ft_strchr(store, '\n') && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed < 0)
			return (free(buff), free(store), store = NULL, buff = NULL, NULL);
		buff[readed] = '\0';
		if (!store)
		{
			store = fill_first(store, buff, readed);
			if (!store)
				return (free(buff), buff = NULL, NULL);
		}
		else
		{
			store = cat_str(store, buff, readed);
			if (!store)
				return (free(buff), buff = NULL, NULL);
		}
	}
	(1) && (free(buff), buff = NULL);
	return (store);
}

static char	*get_line(char *store, char *line)
{
	int	i;

	i = 0;
	if (!store || store[0] == '\0')
		return (NULL);
	while (store[i] != '\n' && store[i] != '\0')
		i++;
	line = malloc(i + 1 + (store[i] == '\n'));
	if (!line)
		return (NULL);
	ft_strlcpy(line, store, i + 1 + (store[i] == '\n'));
	return (line);
}

static char	*after_newline(char *store)
{
	int		i;
	char	*left;

	i = 0;
	if (!store)
		return (NULL);
	while (store[i] != '\n' && store[i])
		i++;
	if (store[i] == '\0')
		return (free(store), store = NULL, NULL);
	left = malloc(sizeof(char) * ft_strlen(store) - i + 1);
	if (!left)
		return (free(store), store = NULL, NULL);
	ft_strlcpy(left, store + i + 1, ft_strlen(store) - i + 1);
	free(store);
	store = NULL;
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*store[OPEN_MAX];
	char		*line;
	char		*buff;
	ssize_t		readed;

	line = NULL;
	buff = NULL;
	readed = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (free(store[fd]), store[fd] = NULL, NULL);
	store[fd] = read_file(fd, store[fd], readed, buff);
	if (!store[fd])
		return (NULL);
	line = get_line(store[fd], line);
	if (!line)
		return (free(store[fd]), store[fd] = NULL, NULL);
	store[fd] = after_newline(store[fd]);
	return (line);
}
