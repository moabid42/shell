/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:46:30 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 18:47:04 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	star_count_dirs(void)
{
	DIR				*dp;
	struct dirent	*dirp;
	int				count;

	count = 0;
	dp = opendir(".");
	if (dp == NULL)
		return (0);
	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] != '.')
			count++;
	}
	closedir(dp);
	return (count);
}

int	star_count(char **tokens)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (!my_strcmp(tokens[i], "*"))
			count++;
		i++;
	}
	return (count);
}

void	star_expend_dir(char **new_tokens, int *i)
{
	DIR				*dp;
	struct dirent	*dirp;

	dp = opendir(".");
	if (dp == NULL)
		return ;
	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] != '.')
		{
			new_tokens[*i] = ft_strdup(dirp->d_name);
			(*i)++;
		}
	}
	closedir(dp);
}

char	**token_expend_star(char **tokens, int prev_size)
{
	char	**new_tokens;
	int		star_num;
	int		dirs;
	int		i;

	i = 0;
	dirs = star_count_dirs();
	star_num = star_count(tokens);
	new_tokens = malloc(sizeof(char *) * (prev_size + dirs * star_num + 1));
	while (*tokens)
	{
		if (!my_strcmp(*tokens, "*"))
		{
			star_expend_dir(new_tokens, &i);
			tokens++;
			continue;
		}
		new_tokens[i] = ft_strdup(*tokens);
		tokens++;
		i++;
	}
	new_tokens[i] = NULL;
	return (new_tokens);
}

bool	star_exist(char **tokens)
{
	int i;
	int j;
	
	i = 0;
	while (tokens[i])
	{
		j = 0;
		while(tokens[i][j])
		{
			if (tokens[i][j] == '*')
				return (true);
			j++;
		}	
		i++;
	}
	return (false);
}
