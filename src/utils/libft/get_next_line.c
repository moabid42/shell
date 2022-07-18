/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:38:02 by sthitiku          #+#    #+#             */
/*   Updated: 2022/05/25 14:32:03 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_and_cpy_reminder(char *str)
{
	char	*new;
	size_t	new_len;
	int		pos;

	if (new_line_checker(str) == -42)
	{
		free(str);
		return (NULL);
	}
	pos = new_line_checker(str);
	new_len = ft_strlen1(str) - pos;
	new = (char *)malloc(sizeof(char) * new_len);
	if (!new)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy1(new, &str[pos + 1], new_len);
	free(str);
	return (new);
}

int	new_line_checker(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-42);
}

char	*return_line(char *str)
{
	char	*ans;
	int		pos;

	pos = new_line_checker(str);
	if (pos < 0)
	{
		ans = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!ans)
		{
			free(str);
			return (NULL);
		}
		ft_strlcpy1(ans, str, ft_strlen(str) + 1);
		return (ans);
	}
	ans = (char *)malloc(sizeof(char) * (pos + 2));
	if (!ans)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy1(ans, str, pos + 2);
	return (ans);
}

char	*read_file(int fd, char *str)
{
	char	buf[BUFFER_SIZE];
	char	*tmp;
	int		fbyte;

	fbyte = read(fd, buf, BUFFER_SIZE);
	if (fbyte <= 0 || str == NULL)
	{
		if (str == NULL || str[0] != '\0')
			return (str);
		free(str);
		return (NULL);
	}
	while (fbyte > 0)
	{
		tmp = (char *)malloc(ft_strlen1(str) + fbyte + 1);
		tmp[0] = '\0';
		ft_strlcpy1(tmp, str, ft_strlen1(str) + 1);
		ft_strlcpy1(&tmp[ft_strlen1(str)], buf, fbyte + 1);
		free(str);
		if (new_line_checker(tmp) != -42)
			break ;
		str = tmp;
		fbyte = read(fd, buf, BUFFER_SIZE);
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static t_read	*head = NULL;
	t_read			*curr;
	char			*ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	curr = check_fd(head, fd);
	if (!curr)
		return (NULL);
	if (!head)
		head = curr;
	curr->str = read_file(fd, curr->str);
	if (!curr->str || *(curr->str) == '\0')
	{
		head = clear_head(head, fd);
		return (NULL);
	}
	ret = return_line(curr->str);
	if (!ret)
	{
		head = clear_head(head, fd);
		return (NULL);
	}
	curr->str = free_and_cpy_reminder(curr->str);
	return (ret);
}
