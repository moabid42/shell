/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:55:30 by sthitiku          #+#    #+#             */
/*   Updated: 2022/05/25 14:31:15 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_read	*clear_head(t_read *read, int fd)
{
	t_read	*after;
	t_read	*curr;

	curr = read;
	after = curr->next;
	if (curr->fd == fd)
	{
		free(curr->str);
		free(curr);
		return (after);
	}
	while (after != NULL)
	{
		if (after->fd == fd)
		{
			curr->next = after->next;
			if (after->str != NULL)
				free(after->str);
			free(after);
			return (read);
		}
		curr = curr->next;
		after = curr->next;
	}
	return (read);
}

size_t	ft_strlen1(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_strlcpy1(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	if (!dstsize || !src)
		return ;
	i = 0;
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return ;
}

t_read	*init_struct(int fd)
{
	t_read	*new;

	new = (t_read *)malloc(sizeof(t_read));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->str = (char *)malloc(sizeof(char));
	new->str[0] = '\0';
	new->next = NULL;
	return (new);
}

t_read	*check_fd(t_read *read, int fd)
{
	t_read	*curr;
	t_read	*ret;

	if (!read)
	{
		read = init_struct(fd);
		if (!read)
			return (NULL);
	}
	curr = read;
	while (curr->next != NULL)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	if (curr->fd != fd)
	{
		ret = init_struct(fd);
		if (!ret)
			return (NULL);
		curr->next = ret;
		return (ret);
	}
	return (curr);
}
