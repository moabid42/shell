/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:08:02 by moabid            #+#    #+#             */
/*   Updated: 2022/10/25 04:43:52 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_weird(struct minishell *minishell)
{
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
	return (!my_strcmp(str, "\"\"")
		|| !my_strcmp(str, "\".\"")
		|| !my_strcmp(str, "<<<<<<")
		|| !my_strcmp(str, "< < < < < <")
		|| !my_strcmp(str, ";;")
		|| !my_strcmp(str, ".")
		|| !my_strcmp(str, ".."));
}

void	minishell_run(struct minishell *minishell)
{
	while (1)
	{
		signal_run(SIGINT);
		termios_echoback(false);
		minishell_get_input(minishell);
		if (is_weird(minishell->input_str))
			handle_weird(minishell);
		else
		{
			if (minishell->input_str == NULL)
			{
				termios_echoback(true);
				break ;
			}
			if (minishell->input_str[0] == 0)
				continue ;
			minishell_read_input(minishell);
		}
	}
}
