/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:32:03 by moabid            #+#    #+#             */
/*   Updated: 2022/10/28 00:51:18 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_heredoc(char *delimiter, int magic, struct s_minishell *m)
{
	char	*line;
	int		fd_out;

	if (magic == 0)
		fd_out = openfile("/tmp/bullshit", 1);
	else
		fd_out = openfile("/tmp/bullshit", 2);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line[ft_strlen(line)] == '\n')
			new_line_remove(line);
		if (!my_strcmp(line, delimiter)
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		line = ft_strjoin(line, "\n");
		if (m->cat_fg == true)
			ft_putstr_fd(line, fd_out);
		free(line);
	}
}

void	heredoc_execute_caller(struct s_ast *tmp, int direction,
			struct s_minishell *m)
{
	if (tmp->left->value.token_type == DOUBLE_SMALLER)
		heredoc_execute_caller(tmp->left, direction, m);
	if (tmp->left->value.token_type != DOUBLE_SMALLER)
	{
		if (direction == 0)
			execute_heredoc(tmp->left->value.token_name, 0, m);
		else
			execute_heredoc(tmp->right->value.token_name, 0, m);
		return ;
	}
	else
		execute_heredoc(tmp->right->value.token_name, 1, m);
}

void	heredoc_forward_command(struct s_ast *ast,
		struct s_minishell *minishell)
{
	pid_t	pid;
	int		fd_in;

	pid = fork();
	if (pid == -1)
		ft_error("FORK ERROR");
	if (!pid)
	{
		fd_in = openfile("/tmp/bullshit", 0);
		dup2(fd_in, 0);
		command_statement_execute_complexe(ast, minishell);
	}
	else
		wait(NULL);
}

void	heredoc_statement_execute(struct s_ast *ast,
	struct s_minishell *m, int out)
{
	struct s_ast	*tmp;
	struct s_ast	*end;

	tmp = ast;
	end = ast_seek_end(tmp);
	(void)out;
	if (end->value.token_type == COMMAND)
		heredoc_execute_caller(tmp, RIGHT, m);
	else
		heredoc_execute_caller(tmp, LEFT, m);
	if (end->value.token_type == COMMAND)
		heredoc_forward_command(end, m);
	else
		print_file("/tmp/bullshit");
}

struct s_ast	*ast_seek_end(struct s_ast *ast)
{
	if (ast->value.token_type == COMMAND || ast->left == NULL)
		return (ast);
	else
		return (ast_seek_end(ast->left));
}
