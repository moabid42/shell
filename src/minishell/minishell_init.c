/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:08:58 by moabid            #+#    #+#             */
/*   Updated: 2022/07/28 17:36:55 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    minishell_create(struct minishell *minishell, char **env)
{
	minishell->env = minishell_env_init(env);
	if (minishell->env == NULL)
		ft_error(MINI_INIT_ERROR);
	minishell->g_env = NULL;
	minishell->prompt = PROMPT;
	minishell->input_str = NULL;
	minishell->variable = false;
	minishell->variables = NULL;
	minishell->scripts = NULL;
}

void 	minishell_get_input(struct minishell *minishell)
{
	//To be implemented
	// if (enviroment_value_get(PROMPT_TITLE))
	// 	minishell->prompt = enviroment_value_get(PROMPT_TITLE);
	int c;
	int bufsize = 1024;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	if (!buffer)
	{
	  	fprintf(stderr, "esh: allocation error\n");
	  	exit(EXIT_FAILURE);
	}	
	while (1)
	{
	  	// Read a character
	  	c = getchar();	
	  	if (c == EOF)
	  		exit(EXIT_SUCCESS);
		else if (c == '\n')
		{
	  		buffer[position] = '\0';
	  		minishell->input_str = buffer;
			return ;
	  	}
		else
	  		buffer[position] = c;
	  	position++;
	  	// If we have exceeded the buffer, reallocate.
	  	if (position >= bufsize)
		{
	    	bufsize += 1024;
	    	buffer = realloc(buffer, bufsize);
	    	if (!buffer)
			{
	    		fprintf(stderr, "esh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}


void    minishell_run(struct minishell *minishell)
{	
	while(1)
	{
		// To do : Handle signals
		// if (!minishell_get_input())
		// {
		// 	ft_putendl_fd("exit", STDERR_FILENO);
		// 	break ;
		// }
		printf("\033[31mesh$\033[0m");
		minishell_get_input(minishell);
		minishell_read_input(minishell);
	}
}

void    minishell_destroy(struct minishell *minishell)
{
	// here we are gonna terminate all the processes and free all the leaks 
	// rl_clear_history();
	// minishell_env_destroy(minishell);
}