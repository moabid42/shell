/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:05:59 by frame             #+#    #+#             */
/*   Updated: 2022/10/26 10:09:45 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

char	*parser(char *cmd, char *paths)
{
	char	*with_slash;
	char	*l_path;
	char	*path;

	with_slash = ft_strrchr(cmd, '/');
	if (with_slash)
	{
		path = ft_strjoin(paths, with_slash);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
	}
	else
	{
		l_path = ft_strjoin(paths, "/");
		path = ft_strjoin(l_path, cmd);
		free(l_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
	}
	free(path);
	return (NULL);
}

char	*ft_special_trim(char *str, int c, int size)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_malloc(sizeof(char) * (size - i));
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[ft_strlen(new)] = '\0';
	return (new);
}

bool	ft_isword(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	my_strcmp(const char *strg1, char *strg2)
{
	if ((strg1 == NULL && strg2 == NULL))
		return (0);
	else if (!strg1 || !strg2)
		return (1);
	while ((*strg1 != '\0' && *strg2 != '\0') && *strg1 == *strg2)
	{
		strg1++;
		strg2++;
	}
	if (*strg1 == *strg2)
		return (0);
	else
		return (*strg1 - *strg2);
}

int	ft_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r' \
	|| c == '\t' || c == '\v' || c == ' ');
}
