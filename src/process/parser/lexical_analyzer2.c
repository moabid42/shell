/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:09:18 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 15:09:59 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

void	print_tokens(char **scripts_line, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("The token value is : %s\n", scripts_line[i]);
		i++;
	}
}

bool	minishell_scripts_parse(struct s_minishell *minishell)
{
	char	**scripts_line;

	scripts_line = ft_new_split(minishell->input_str, ';', "\"'");
	minishell->scripts_num = words_count(minishell->input_str, ';', "\"'");
	if (minishell->scripts_num == 1)
		minishell->scripts = ft_create_node_script(scripts_line[0]);
	else
		minishell->scripts = ft_create_stack_scripts(scripts_line,
				minishell->scripts_num);
	if (minishell->scripts == NULL)
		return (false);
	return (true);
}

void	printer_split(char **tokens)
{
	while (*tokens)
	{
		dprintf(2, "The token is : %s\n", *tokens);
		tokens++;
	}
}

int	star_count_dirs(void)
{
	DIR				*dp;
	struct dirent	*dirp;
	int				count;

	count = 0;
	dp = opendir(".");
	if (dp == NULL)
		return (0);
	while ((readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] != '.')
			count++;
	}
	closedir(dp);
	return (count);
}

int	star_count(char **tokens)
{
	int	i;
	int	count;

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
