/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:09:34 by kben-tou          #+#    #+#             */
/*   Updated: 2024/12/13 17:52:54 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	str_len;
	size_t	i;

	i = 0;
	str_len = ft_strlen(src);
	if (dstsize == 0)
		return (str_len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (str_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (dstsize + ft_strlen(src));
	while (src[i] && dst_len + i < dstsize - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + ft_strlen(src));
}

char	*fill_first(char *store, char *buff, ssize_t readed)
{
	if (!buff)
		return (NULL);
	store = malloc(sizeof(char) * (readed + 1));
	if (!store)
		return (NULL);
	ft_strlcpy(store, buff, readed + 1);
	return (store);
}

char	*cat_str(char *store, char *buff, ssize_t readed)
{
	size_t	new_size;
	char	*new_store;

	if (!buff)
		return (free(store), store = NULL, NULL);
	new_size = ft_strlen(store) + readed + 1;
	new_store = malloc(new_size * sizeof(char));
	if (!new_store)
		return (free(store), store = NULL, NULL);
	ft_strlcpy(new_store, store, ft_strlen(store) + 1);
	ft_strlcat(new_store, buff, new_size);
	free(store);
	return (new_store);
}
