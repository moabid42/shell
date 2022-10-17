/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:59:16 by moabid            #+#    #+#             */
/*   Updated: 2022/10/17 14:08:37 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"

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

void	freeme(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*get_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path;
	t_env	*head;
	int i;

	head = env;
	while (ft_strnstr(head->name, "PATH", 4) == 0 && head)
		head = head->next;
	if(!head)
		return (NULL);
	paths = ft_split(head->content, ':');
	i = 0;
	while (paths[i])
	{
		path = parser(cmd, paths[i]);
		if (path)
			return (path);
		i++;
	}
	freeme(paths);
	return (NULL);
}

bool	ft_iscommand(char *str, t_env *env)
{
	if (get_path(str, env))
		return (true);
	return (false);
}

bool	ft_isfile(char *str)
{
	if (access(str, F_OK))
		return (true);
	return (false);
}
