/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_executing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:36:12 by moabid            #+#    #+#             */
/*   Updated: 2022/08/14 05:42:39 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include "execute.h"

void	command_statement_run(char **command_statement, char *command_path, struct minishell *minishell)
{
	if (execve(command_path, command_statement, minishell->env) == -1)
			ft_error(command_statement[0]);
}

int	ast_child_num(struct ast *node)
{
	int num;
	struct ast *tmp;

	num = 0;
	tmp = node;
	if (tmp->right)
		num++;
	while (tmp->left)
	{
		num++;
		tmp = tmp->left;
	}
	return (num);
}

char	**command_statement_create_complexe(struct ast *ast)
{
	int			i;
	struct ast	*tmp;
	char		**command_statement;

	i = 0;
	tmp = ast;
	command_statement = ft_malloc(sizeof(char *) * (ast_child_num(ast) + 2));
	command_statement[i] = ft_strdup(tmp->value.token_name);
	if (tmp->left)
		command_statement[++i] = ft_strdup(tmp->left->value.token_name);
	if (tmp->right)
		command_statement[++i] = ft_strdup(tmp->right->value.token_name);
	if (tmp->left)
	{
		tmp = tmp->left;
		while (tmp->left)
		{
			command_statement[++i] = ft_strdup(tmp->left->value.token_name);
			tmp = tmp->left;
		}
	}
	command_statement[ast_child_num(ast) + 1] = NULL;
	return (command_statement);
}

void	command_statement_execute_complexe(struct ast *ast, struct minishell *minishell)
{
	char 	**command_statement;
	char	*command_path;

	command_statement = command_statement_create_complexe(ast);
	// printer_split(command_statement);
	command_path = get_path(command_statement[0], minishell->env);
	command_statement_run(command_statement, command_path, minishell);
	command_statement_destroy(command_statement);
}

void	process_pipe_run_left(struct ast *ast, struct minishell *minishell)
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
		command_statement_execute_complexe(ast->left, minishell);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		waitpid(pid2, NULL, 0);
	}
}

void	process_pipe_run_right(struct ast *ast, struct minishell *minishell)
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
		command_statement_execute_complexe(ast->right, minishell);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		waitpid(pid2, NULL, 0);
	}
}

void	process_pipe_run_first(struct ast *ast,struct ast *first, struct minishell *minishell)
{
	if (ast->left->value.token_type == PIPE)
		process_pipe_run_first(ast->left, first, minishell);
	if (ast->left->value.token_type != PIPE)
		process_pipe_run_left(ast, minishell);
	if (ast->right != first->right)
		process_pipe_run_right(ast, minishell);
	else
		command_statement_execute_complexe(first->right, minishell);
}

void	process_redirect_left(struct ast *ast)
{
	int	fd_in;

	fd_in = openfile(ast->left->value.token_name, 0);
	if (fd_in == -1)
		ft_error("File not found\n");
	dup2(fd_in, 0);
}

void	redirection_run(struct ast *ast,struct ast *first, struct minishell *minishell)
{
	if (ast->left->value.token_type == PIPE)
		redirection_run(ast->left, first, minishell);
	if (ast->left->value.token_type != PIPE)
	{
		process_redirect_left(ast->left);
		// printf("We are gonna run %s\n", ast->right->value.token_name);
		process_pipe_run_right(ast, minishell);
	}
	if (ast->right != first->right)
	{
		// printf("We are running a a pipe with %s\n", ast->right->value.token_name);
		process_pipe_run_right(ast, minishell);
	}
	else
	{
		// printf("We are gonna execute this command %s\n", ast->right->value.token_name);
		command_statement_execute_complexe(first->right, minishell);
	}
}

bool	redirection_exist(struct ast *ast)
{
	while (1)
	{
		if (ast == NULL)
			return (false);
		else if (ast->value.token_type == LESS)
			return (true);
		ast = ast->left;
	}
	return (false);
}

void	minishell_process_command_pipe(struct ast *ast, struct minishell *minishell)
{
	pid_t	pid;
	struct ast *tmp;
	struct ast *tmp2;

	pid = fork();
	tmp = ast;
	tmp2 = ast;
	if (pid == -1)
		ft_error("fork error");
	if (!pid)
	{
		if (redirection_exist(tmp) == true)
			redirection_run(tmp2, ast, minishell);
		else
		{
			// printf("hi\n");
			process_pipe_run_first(tmp, ast, minishell);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

void	minishell_process_pipeline(struct ast *ast, struct minishell *minishell)
{
	minishell_process_command_pipe(ast, minishell);
}