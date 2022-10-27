/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:59:55 by moabid            #+#    #+#             */
/*   Updated: 2022/10/28 00:48:12 by moabid           ###   ########.fr       */
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

int	get_number_pipes(struct s_ast *ast, int count)
{
	if (ast->value.token_type == PIPE)
		get_number_pipes(ast->left, count++);
	return (count);
}

void	minishell_process_command_pipe(struct s_ast *ast,
			struct s_minishell *minishell, int type)
{
	pid_t	pid;
	int		status;
	int		i;

	ini_var(&i, &status, minishell, ast);
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
	return_value(status, minishell);
}

void	process_pipe_run_right(struct s_ast *ast, struct s_minishell *minishell)
{
	pid_t	pid2;
	int		pfd[2];

	if (pipe(pfd) == -1)
		ft_error("pipe error");
	pid2 = fork();
	minishell->pids[minishell->pid_count++] = pid2;
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
	minishell->pids[minishell->pid_count++] = pid2;
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
