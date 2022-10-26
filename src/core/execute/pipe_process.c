/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:59:55 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:25:07 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_pipe_run_first(struct s_ast *ast,
			struct s_ast *first, struct s_minishell *minishell, int fd_out)
{
	if (ast->left->value.token_type == PIPE)
		process_pipe_run_first(ast->left, first, minishell, fd_out);
	if (ast->left->value.token_type != PIPE)
		process_pipe_run_left(ast, minishell);
	if (ast->right != first->right)
		process_pipe_run_right(ast, minishell);
	else
		minishell_ast_execute(ast->right, minishell);
}

void	minishell_process_command_pipe(struct s_ast *ast,
			struct s_minishell *minishell, int type)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		ft_error("fork error");
	if (!pid)
	{
		if (type == OVERWRITE)
			process_redirect_overwrite(ast, minishell);
		else if (type == APPEND)
			process_redirect_append(ast, minishell);
		else
			process_direct(ast, minishell);
		exit(minishell->return_value);
	}
	else
		waitpid(pid, &status, 0);
	if (status == 32512)
		minishell->return_value = 127;
	else if (status != 0)
		minishell->return_value = 1;
	else
		minishell->return_value = 0;
}

void	process_pipe_run_right(struct s_ast *ast, struct s_minishell *minishell)
{
	pid_t	pid2;
	int		pfd[2];

	if (pipe(pfd) == -1)
		ft_error("pipe error");
	pid2 = fork();
	if (pid2 == -1)
		ft_error("fork error");
	if (!pid2)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		minishell_ast_execute(ast->right, minishell);
		exit(minishell->return_value);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
	}
}

void	process_pipe_run_left(struct s_ast *ast, struct s_minishell *minishell)
{
	pid_t	pid2;
	int		pfd[2];

	if (pipe(pfd) == -1)
		ft_error("pipe error");
	pid2 = fork();
	if (pid2 == -1)
		ft_error("fork error");
	if (!pid2)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		minishell_ast_execute(ast->left, minishell);
		exit(minishell->return_value);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
	}
}
