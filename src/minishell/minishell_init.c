/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:08:58 by moabid            #+#    #+#             */
/*   Updated: 2022/08/19 04:41:20 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void 	get_input(struct minishell *minishell);

void    minishell_create(struct minishell *minishell, char **env)
{
	minishell->env = minishell_env_init(env);
	if (minishell->env == NULL)
		ft_error(MINI_INIT_ERROR);
	minishell->g_env = NULL;
	minishell->prompt = PROMPT;
	minishell->input_str = NULL;
	minishell->variables = NULL;
	minishell->scripts = NULL;
}

void 	minishell_get_input(struct minishell *minishell)
{
	//Signal to be implemented
	if (isatty(STDIN_FILENO))
		minishell->input_str = readline("\033[31mesh$\033[0m ");
	else
		get_input(minishell);
	if (!minishell->input_str)
		return ;
	if (isatty(STDIN_FILENO))
		add_history(minishell->input_str);
}

void	signal_ctlc(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}


void 	get_input(struct minishell *minishell)
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

// void    minishell_run(struct minishell *minishell)
// {	
// 	signal(SIGQUIT, SIG_IGN);
// 	while(1)
// 	{
// 		// To do : Handle signals
// 		signal(SIGINT, signal_ctlc);
// 		minishell_get_input(minishell);
// 	  	if (my_strcmp(minishell->input_str, "exit") == 0)
// 		{
// 			ft_putendl_fd("exit", STDERR_FILENO);
// 	  		break;
// 		}
// 		minishell_read_input(minishell);
// 	}
// }

void    minishell_run(struct minishell *minishell)
{
	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		// To do : Handle signals
		signal(SIGINT, signal_ctlc);
		minishell_get_input(minishell);
	  	if (my_strcmp(minishell->input_str, "exit") == 0)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
	  		exit(EXIT_SUCCESS);
		}
		minishell_read_input(minishell);
	}
}

void    minishell_destroy(struct minishell *minishell)
{
	// here we are gonna terminate all the processes and free all the leaks 
	// rl_clear_history();
	// minishell_env_destroy(minishell);
}