/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:08:58 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 14:16:51 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

char	*get_input_terminal(int fd);

void    minishell_create(struct minishell *minishell, char **env)
{
	minishell->env = minishell_env_init(env);
	if (minishell->env == NULL)
		ft_error(MINI_INIT_ERROR);
	minishell->g_env = NULL;
	minishell->return_value = 0;
	minishell->prompt = PROMPT;
	minishell->input_str = NULL;
	minishell->variables = NULL;
	minishell->scripts = NULL;
	minishell->byte_code = 0;
	minishell->brakets_flag = 0;
	minishell->index_flag = 1;
	minishell->handled = false;
}

int	ft_strlen_newline(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] > 31 && str[i] < 127)
		i++;
	return(i);
}

void 	minishell_get_input(struct minishell *minishell)
{
	//Signal to be implemented
	if (isatty(STDIN_FILENO))
	{
		minishell->input_str = readline("\033[31mesh$\033[0m ");
		minishell->input_len = ft_strlen_newline(minishell->input_str);
		minishell->type = SIMPLE;
	}
	else
	{
		minishell->input_str = get_input_terminal(STDIN_FILENO);
		minishell->type = COMPLEXE;
	}
	if (!minishell->input_str)
		return ;
	if (isatty(STDIN_FILENO))
		add_history(minishell->input_str);
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
			return (ft_strtrim(line, "\n"));
		check = read(fd, &buffer, 1);
	}
	if (check == -1)
		return (ft_free(line));
	return (line);
}

int	termios_echoback(bool echo_ctl_chr)
{
	struct termios	terminos_p;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (1);
	terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (1);
	return (0);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		// minishell->return_value = 1;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();//Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
		rl_replace_line("", 0);//removes the content of the line with texts which is "" here
		rl_redisplay(); //Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
	}
}

void	signal_run(int sig)
{
	struct sigaction	sig_action;

	sig_action.sa_handler = handler;
	if (sigaction(sig, &sig_action, NULL) == -1)
		return ;
	sigaction(SIGINT, &sig_action, NULL);
	signal(SIGQUIT, SIG_IGN);
}

bool	are_weird(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

void	handle_weird(struct minishell *minishell)
{
	if (!my_strcmp(minishell->input_str, "\"\""))
	{
		dprintf(2, "esh: : command not found\n");
		minishell->return_value = 127;
	}
	else if (!my_strcmp(minishell->input_str, "\".\"")
		|| !my_strcmp(minishell->input_str, "..")
		|| !my_strcmp(minishell->input_str, "."))
	{
		dprintf(2, "esh: .: filename argument required\n");
		dprintf(2, ".: usage: . filename [arguments]\n");
		minishell->return_value = 2;
	}
	else if (!my_strcmp(minishell->input_str, ";;")
		|| !my_strcmp(minishell->input_str, "<")
		|| !my_strcmp(minishell->input_str, ">")
		|| !my_strcmp(minishell->input_str, "< < < < < <"))
	{
		dprintf(2, "esh: syntax error near unexpected token `%s'\n", minishell->input_str);
		minishell->return_value = 258;
	}
	else if (!my_strcmp(minishell->input_str, "<<<<<<"))
	{
		dprintf(2, "esh: syntax error near unexpected token `<<<'\n");
		minishell->return_value = 258;
	}
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

void    minishell_run(struct minishell *minishell)
{
	while(1)
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
			if(minishell->input_str[0] == 0)
				continue;
			minishell_read_input(minishell);
		}
	}
}

void    minishell_destroy(struct minishell *minishell)
{
	// here we are gonna terminate all the processes and free all the leaks 
	rl_clear_history();
	// minishell_env_destroy(minishell);
}