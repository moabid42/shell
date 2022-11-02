/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:08:02 by moabid            #+#    #+#             */
/*   Updated: 2022/10/28 16:31:49 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	handle_weird(struct s_minishell *minishell)
{
	if (is_only_space(minishell->input_str) == true)
		return ;
	if (!my_strcmp(minishell->input_str, "\"\""))
		error_exit(minishell, "esh: :command not found\n",
			NULL, 127);
	else if (!my_strcmp(minishell->input_str, "\".\"")
		|| !my_strcmp(minishell->input_str, "..")
		|| !my_strcmp(minishell->input_str, "."))
		error_exit(minishell, "esh: .: filename argument required\n",
			".: usage: . filename [arguments]\n", 127);
	else if (!my_strcmp(minishell->input_str, ";;")
		|| !my_strcmp(minishell->input_str, "<")
		|| !my_strcmp(minishell->input_str, ">")
		|| !my_strcmp(minishell->input_str, "< < < < < <"))
		error_exit(minishell, "esh: syntax error near unexpected token `",
			minishell->input_str, 258);
	else if (!my_strcmp(minishell->input_str, "<<<<<<"))
		error_exit(minishell, "esh: syntax error near unexpected token `<<<'\n",
			NULL, 258);
}

bool	is_weird(char *str)
{
	return (is_only_space(str) == true
		|| !my_strcmp(str, "\"\"")
		|| !my_strcmp(str, "\".\"")
		|| !my_strcmp(str, "<<<<<<")
		|| !my_strcmp(str, "< < < < < <")
		|| !my_strcmp(str, ";;")
		|| !my_strcmp(str, ".")
		|| !my_strcmp(str, ".."));
}

void	minishell_run(struct s_minishell *minishell)
{
	while (1)
	{
		signal_run(SIGINT);
		termios_echoback(false);
		minishell_get_input(minishell);
		if (!minishell->input_str)
			break ;
		if (is_weird(minishell->input_str))
			handle_weird(minishell);
		else
		{
			if (minishell->input_str == NULL)
				break ;
			if (minishell->input_str[0] == 0)
				continue ;
			minishell_read_input(minishell);
		}
		while (minishell->cat_num-- > 0)
		{
			get_input_terminal(STDIN_FILENO);
			minishell->cat_num--;
		}
	}
}
