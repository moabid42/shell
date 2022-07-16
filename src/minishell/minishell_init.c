/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:08:58 by moabid            #+#    #+#             */
/*   Updated: 2022/07/13 23:49:16 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    minishell_create(struct minishell *minishell)
{
	minishell->env = minishell_env_init(minishell, env);
	if (minishell->env == NULL)
		ft_error(MINI_INIT_ERROR);
	minishell->g_env = NULL;
	minishell->prompt = PROMPT;
	minishell->input = NULL;
	minishell->variable = false;
	minishell->variables = NULL;
}

bool	minishell_get_input(struct minishell *minishell)
{
	//To be implemented
	// if (enviroment_value_get(PROMPT_TITLE))
	// 	minishell->prompt = enviroment_value_get(PROMPT_TITLE);
	char	*input;

	input = readline(minishell->prompt);
	if (input == NULL)
		return (false);
	add_history(input);
	minishell->input = input;
	return (true);
}

void    minishell_run(struct minishell *minishell)
{	
	while(1)
	{
		// To do : Handle signals
		if (!minishell_get_input(minishell))
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		minishell_process_input(minishell);
	}
}

void    minishell_destroy(struct minishell *minishell)
{
	// here we are gonna terminate all the processes and free all the leaks 
	rl_clear_history();
	minishell_env_destroy(minishell);
}