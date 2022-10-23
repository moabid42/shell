/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:08:58 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 17:16:27 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

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

void 	minishell_get_input(struct minishell *minishell)
{
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

void    minishell_destroy(struct minishell *minishell)
{
	rl_clear_history();
}