/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:05:47 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:07:24 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redirection_exist(struct ast *ast)
{
	struct ast	*tmp;

	tmp = ast;
	while (1)
	{
		if (tmp == NULL)
			return (false);
		else if (tmp->value.token_type == LESS)
			return (true);
		tmp = tmp->left;
	}
	return (false);
}

void	process_redirect_left(struct ast *ast)
{
	int	fd_in;

	fd_in = openfile(ast->left->value.token_name, 0);
	if (fd_in == -1)
	{
		dprintf(2, "esh: %s: No such file or directory\n",
			ast->left->value.token_name);
		exit(1);
	}
	dup2(fd_in, 0);
}

void	process_direct(struct ast *ast, struct minishell *minishell)
{
	struct ast	*tmp;

	tmp = ast;
	minishell->redirection = DIRECT;
	if (redirection_exist(tmp) == true)
		redirection_run(tmp, ast, minishell, 1);
	else
		process_pipe_run_first(tmp, ast, minishell, 1);
}

void	process_redirect_overwrite(struct ast *ast, struct minishell *minishell)
{
	int			fd_out;
	struct ast	*tmp;

	tmp = ast;
	minishell->redirection = OVERWRITE;
	fd_out = openfile(tmp->right->value.token_name, 1);
	if (redirection_exist(tmp->left) == true)
		redirection_run(tmp->left, ast->left, minishell, fd_out);
	else
		process_pipe_run_first(tmp->left, ast->left, minishell, fd_out);
}

void	process_redirect_append(struct ast *ast, struct minishell *minishell)
{
	int			fd_out;
	struct ast	*tmp;

	tmp = ast;
	minishell->redirection = APPEND;
	fd_out = openfile(tmp->right->value.token_name, 2);
	if (redirection_exist(tmp->left) == true)
		redirection_run(tmp->left, ast->left, minishell, fd_out);
	else
		process_pipe_run_first(tmp->left, ast->left, minishell, fd_out);
}
