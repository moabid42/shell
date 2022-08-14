/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_crossing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:36:31 by moabid            #+#    #+#             */
/*   Updated: 2022/08/14 22:44:06 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

// int	ast_child_num(struct ast *node)
// {
// 	int num;

// 	num = 0;
// 	if (node->left)
// 		num++;
// 	if (node->right)
// 		num++;
// 	return (num);
// }

//create a function that counts the number of children of a node

int	ast_child_num_complexe(struct ast *node)
{
	int num;
	struct ast *tmp;

	num = 0;
	tmp = node;
	if (tmp->left)
		num++;
	if (tmp->right)
	{
		num++;
		tmp = tmp->right;
		while (tmp->left)
		{
			num++;
			tmp = tmp->left;
		}
	}
	return (num);
}

//create a function that prints the elements of command_statement
void	printerr(char **command_statement)
{
	int i;

	i = 0;
	while (command_statement[i])
	{
		printf("Elements are %s\n", command_statement[i]);
		i++;
	}
}

char	**command_statement_create(struct ast *ast)
{
	int			i;
	struct ast	*tmp;
	char		**command_statement;

	i = 0;
	tmp = ast;
	command_statement = ft_malloc(sizeof(char *) * (ast_child_num_complexe(ast) + 2));
	command_statement[i] = ft_strdup(tmp->value.token_name);
	if (tmp->left)
		command_statement[++i] = ft_strdup(tmp->left->value.token_name);
	if (tmp->right)
	{
		command_statement[++i] = ft_strdup(tmp->right->value.token_name);
		tmp = tmp->right;
		while (tmp->left)
		{
			command_statement[++i] = ft_strdup(tmp->left->value.token_name);
			tmp = tmp->left;
		}
	}
	command_statement[ast_child_num_complexe(ast) + 1] = NULL;
	// printerr(command_statement);
	return (command_statement);
}

void	command_statement_destroy(char **command_statement)
{
	int i;

	i = 0;
	while (command_statement[i])
	{
		free(command_statement[i]);
		i++;
	}
	free(command_statement);
}

void	command_statement_execute(char **command_statement, char *path, struct minishell *minishell, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("FORK ERROR");
	if (!pid)
	{
		dup2(fd_out, 1);
		if (execve(path, command_statement, minishell->env) == -1)
			ft_error(command_statement[0]);
	}
	else
		wait(NULL);
}

int	openfile(char *file, int re_or_wr)
{
	int	ret;

	if (re_or_wr == 0)
	{
		ret = open(file, O_RDONLY, 0777);
		if (access(file, F_OK | R_OK) != 0)
			ft_error("File not found");
	}
	if (re_or_wr == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (re_or_wr == 2)
		ret = open(file , O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}

void	file_reader(int fd_in)
{
	char	*line;
	while (1)
	{
		line = get_next_line(fd_in);
		if (line == NULL)
			break ;
		printf("%s", line);
	}
	printf("\n");
}

void	less_statement_execute_child(char **command_statement, struct ast *ast, struct minishell *minishell)
{
	int		fd_in;

	fd_in = openfile(command_statement[1], 0);
	if (fd_in == -1)
		ft_error("File not found\n");
	if (ast->right == NULL)
		file_reader(fd_in);
	else
	{
		dup2(fd_in, 0);
		command_statement_execute_complexe(ast->right, minishell);
	}
	close(fd_in);
}

void	less_statement_execute(char **command_statement, struct ast *ast, struct minishell *minishell, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("FORK ERROR");
	if (!pid)
	{
		dup2(fd_out, 1);
		less_statement_execute_child(command_statement, ast, minishell);
	}
	else
		wait(NULL);
}

void	print_file(char  *file)
{
	int fd;
	char *line;

	fd = open(file, O_RDONLY, 0777);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
}

void	execute_heredoc(char *delimiter, int magic)
{
	char	*line;
	int     fd_out;

	if (magic == 0)
		fd_out = openfile("/tmp/bullshit", 1);
	else
		fd_out = openfile("/tmp/bullshit", 2);
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_out);
		free(line);
	}
}

void	heredoc_execute_caller(struct ast *tmp)
{
	// int	i;

	// i = 0;
	// while (tmp->left->value.token_type == DOUBLE_SMALLER)
	// {
	// 	execute_heredoc(tmp->right->value.token_name, i);
	// 	tmp = tmp->left;
	// 	i++;
	// }
	if (tmp->left->value.token_type == DOUBLE_SMALLER)
		heredoc_execute_caller(tmp->left);
	if (tmp->left->value.token_type != DOUBLE_SMALLER)
	{
		execute_heredoc(tmp->left->value.token_name, 0);
		return ;
	}
	else
		execute_heredoc(tmp->right->value.token_name, 1);
}

void	heredoc_statement_execute(struct ast *ast, struct minishell *minishell)
{
	pid_t	pid;
	struct ast	*tmp;

	tmp = ast;
	pid = fork();
	if (pid == -1)
		ft_error("FORK ERROR");
	if (!pid)
	{
		heredoc_execute_caller(tmp);
		print_file("/tmp/bullshit");
	}
	else
		wait(NULL);
}

void	minishell_process_command(struct ast *ast, struct minishell *minishell)
{
	int		fd_out;
	struct ast	*jump;
	char 	**command_statement;
	char	*command_path;

	jump = ast;
	if (ast->value.token_type == GREATER)
	{
		fd_out = openfile(ast->right->value.token_name, 1);
		jump = jump->left;
	}
	else if (ast->value.token_type == DOUBLE_GREATER)
	{
		fd_out = openfile(ast->right->value.token_name, 2);
		jump = jump->left;
	}
	else
		fd_out = 1;
	command_statement = command_statement_create(jump);
	command_path = get_path(command_statement[0], minishell->env);
	if (ast->value.token_type == COMMAND
		|| ast->left->value.token_type == COMMAND)
		command_statement_execute(command_statement, command_path, minishell, fd_out);
	else if (ast->left->value.token_type == LESS)
		less_statement_execute(command_statement, ast->left, minishell, fd_out);
	else if (ast->value.token_type == LESS)
		less_statement_execute(command_statement, ast, minishell, fd_out);
	else
		heredoc_statement_execute(ast, minishell);
	command_statement_destroy(command_statement);
}

void	minishell_process_bool(struct ast *ast, struct minishell *minshell)
{
	if (ast->value.token_type == TRUE)
		write(1, "0\n", 2);
	else
		write(1, "1\n", 2);
}

bool	ast_is_simple(struct ast *ast)
{
	if (ast->value.token_type == COMMAND
		|| ast->value.token_type == DOUBLE_SMALLER
		|| ast->value.token_type == LESS
		|| (ast->value.token_type == GREATER
		&& ast->left->value.token_type != PIPE)
		|| (ast->value.token_type == DOUBLE_GREATER
		&& ast->left->value.token_type != PIPE))
		return (true);
	return (false);
}

void	minishell_ast_execute(struct ast *ast, struct minishell *minishell)
{
	struct ast *tmp;

	tmp = ast;
	if (!ast)
		return ;
	if (ast_is_simple(ast) == true)
		minishell_process_command(ast, minishell);
	else if (ast->value.token_type == FALSE
		|| ast->value.token_type == TRUE)
		minishell_process_bool(ast, minishell);
	else if (ast->value.token_type == PIPE
		|| ast->value.token_type == GREATER
		|| ast->value.token_type == DOUBLE_GREATER)
		minishell_process_pipeline(tmp, minishell);
	// else if (ast->value.token_type == DOUBLE_SMALLER
	// 	|| ast->value.token_type == LESS)
	// 	minishell_process_redirection_open(ast, minishell);
	// // else if (ast->value.token_type == LESS)
	// else if (ast->value.token_type == ANDAND
	// 	|| ast->value.token_type == OROR)
	// 	minishell_process_and_or(ast, minishell);
	// else if (ast->value.token_type == AST_SUBSHELL)
	// 	minishell_process_subshell(ast, minishell);
	// else if (ast->value.token_type == AST_COMMAND_LIST)
	// 	minishell_process_command_list(ast, minishell);
}