/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:10:02 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 15:11:22 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

void	star_expend_dir(char **new_tokens, int *i)
{
	DIR				*dp;
	struct dirent	*dirp;

	dp = opendir(".");
	if (dp == NULL)
		return ;
	while ((readdir(dp)) != NULL)
	{
		dirp = readdir(dp);
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
			continue ;
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
	int	i;
	int	j;

	i = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			if (tokens[i][j] == '*')
				return (true);
			j++;
		}	
		i++;
	}
	return (false);
}

/*	create a function that is gonna count the number of tokens */
int	count_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

void	minishell_set_byte_code(struct s_minishell *minishell)
{
	long long	i;
	int			j;
	long long	edx;

	i = 1;
	i <<= 32;
	j = 0;
	edx = 0;
	while (j < minishell->input_len)
	{
		if (ft_strnstr(minishell->input_str + j, "&&", 3))
		{
			edx = edx | i;
			i *= 2;
			j += 2;
		}
		else if (ft_strnstr(minishell->input_str + j, "||", 3))
		{
			i *= 2;
			j += 2;
		}
		else
			j++;
	}
	minishell->byte_code = edx;
}
