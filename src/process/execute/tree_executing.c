/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_executing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:36:12 by moabid            #+#    #+#             */
/*   Updated: 2022/08/24 16:25:41 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include "execute.h"

bool	is_builtin(char *cmd)
{
	return (!my_strcmp(cmd, "exit")
		|| !my_strcmp(cmd, "export")
		|| !my_strcmp(cmd, "cd")
		|| !my_strcmp(cmd, "echo")
		|| !my_strcmp(cmd, "env")
		|| !my_strcmp(cmd, "pwd")
		|| !my_strcmp(cmd, "unset"));
}

void	builtin_run(char **cmd_list, struct minishell *minishell)
{
	if (!my_strcmp(cmd_list[0], "exit"))
		ft_exit(cmd_list, minishell);
}

void	command_statement_run(char **command_statement, char *command_path, struct minishell *minishell)
{
	if(is_builtin(command_statement[0]) == true)
		builtin_run(command_statement, minishell);
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
	// dprintf(2, "The number of the childs is : %d for %s\n", ast_child_num_complexe(ast) + 1, tmp->value.token_name);
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
		minishell_ast_execute(ast->left, minishell);
		exit(minishell->return_value);
	}
	else
	{
		// dprintf(2, "The status for left is : %d\n", minishell->return_value);
		// waitpid(pid2, NULL, 0);
		close(pfd[1]);
		dup2(pfd[0], 0);
	}
}

void	process_pipe_run_right(struct ast *ast, struct minishell *minishell)
{
	pid_t	pid2;
	int		pfd[2];

	// dprintf(2, "We are running the command in the node %s\n", ast->value.token_name);
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
		// dprintf(2, "The status for right is : %d\n", minishell->return_value);
		close(pfd[1]);
		dup2(pfd[0], 0);
		// waitpid(pid2, NULL, 0);
	}
}

void	process_pipe_run_first(struct ast *ast,struct ast *first, struct minishell *minishell, int fd_out)
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

void	process_redirect_left(struct ast *ast)
{
	int	fd_in;

	fd_in = openfile(ast->left->value.token_name, 0);
	if (fd_in == -1)
		ft_error("File not found\n");
	dup2(fd_in, 0);
}

void	redirection_run(struct ast *ast,struct ast *first, struct minishell *minishell, int fd_out)
{
	if (ast->left->value.token_type == PIPE)
		redirection_run(ast->left, first, minishell, fd_out);
	if (ast->left->value.token_type != PIPE)
		process_pipe_run_left(ast->left, minishell);
	if (ast->right != first->right)
		process_pipe_run_right(ast, minishell);
	else
		minishell_ast_execute(ast->right, minishell);
}

bool	redirection_exist(struct ast *ast)
{
	struct ast *tmp;

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

void	process_direct(struct ast *ast, struct minishell *minishell)
{
	struct ast *tmp;

	tmp = ast;
	minishell->redirection = DIRECT;
	if (redirection_exist(tmp) == true)
		redirection_run(tmp, ast, minishell, 1);
	else
		process_pipe_run_first(tmp, ast, minishell, 1);
}

void	process_redirect_overwrite(struct ast *ast, struct minishell *minishell)
{
	int fd_out;
	struct ast *tmp;

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
	int fd_out;
	struct ast *tmp;

	tmp = ast;
	minishell->redirection = APPEND;
	fd_out = openfile(tmp->right->value.token_name, 2);
	if (redirection_exist(tmp->left) == true)
		redirection_run(tmp->left, ast->left, minishell, fd_out);
	else
		process_pipe_run_first(tmp->left, ast->left, minishell, fd_out);
}

void	minishell_process_command_pipe(struct ast *ast, struct minishell *minishell, int type)
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
	if (status != 0)
		minishell->return_value = 1;
	else
		minishell->return_value = 0;
	// dprintf(2, "The return status is : %d of that\n", minishell->return_value);
}

void	minishell_process_pipeline(struct ast *ast, struct minishell *minishell)
{
	// printf("The type is %d\n", ast->value.token_type);
	if (ast->value.token_type == PIPE)
		minishell_process_command_pipe(ast, minishell, DIRECT);
	else if (ast->value.token_type == GREATER)
		minishell_process_command_pipe(ast, minishell, OVERWRITE);
	else
		minishell_process_command_pipe(ast, minishell, APPEND);
}