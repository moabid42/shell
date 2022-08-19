/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:08:58 by moabid            #+#    #+#             */
/*   Updated: 2022/08/19 06:20:48 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*get_input_terminal(int fd);

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
		minishell->input_str = get_input_terminal(STDIN_FILENO);
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

	//To be implemented
	// if (enviroment_value_get(PROMPT_TITLE))
	// 	minishell->prompt = enviroment_value_get(PROMPT_TITLE);

char	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

char	*append_chr(char *str, char append)
{
	char	*new_str;
	int		i;

	if (str == NULL)
		return (NULL);
	new_str = ft_malloc(ft_strlen(str) + 2);
	if (new_str != NULL)
	{
		i = 0;
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = append;
		new_str[i + 1] = '\0';
	}
	free(str);
	return (new_str);
}

char	*get_input_terminal(int fd)
{
	char	*line;
	char	buffer;
	int		check;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	check = read(fd, &buffer, 1);
	if (check == -1 || check == 0)
		return (ft_free(line));
	while (check > 0)
	{
		line = append_chr(line, buffer);
		if (line == NULL)
			return (NULL);
		if (buffer == '\n')
			return (line);
		check = read(fd, &buffer, 1);
	}
	if (check == -1)
		return (ft_free(line));
	return (line);
}

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
	rl_clear_history();
	// minishell_env_destroy(minishell);
}