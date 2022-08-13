/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_crossing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:36:31 by moabid            #+#    #+#             */
/*   Updated: 2022/08/13 02:59:06 by moabid           ###   ########.fr       */
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

void	command_statement_execute(char **command_statement, char *path, struct minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("FORK ERROR");
	if (!pid)
	{
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

void	less_statement_execute(char **command_statement, struct minishell *minishell)
{
	pid_t	pid;
	char	buffer[256];
	int		fd_in;

	pid = fork();
	if (pid == -1)
		ft_error("FORK ERROR");
	if (!pid)
	{
		fd_in = openfile(command_statement[1], 0);
		if (fd_in == -1)
			ft_error("File not found\n");
		else
			read(fd_in, &buffer, sizeof(buffer));
	}
	else
		wait(NULL);
	printf("%s", buffer);
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

void	execute_heredoc(char **argv)
{
	char	*line;
	int     fd_out;

	fd_out = openfile("/tmp/bullshit", 1);
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (ft_strncmp(line, argv[1], ft_strlen(argv[1])) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_out);
		free(line);
	}
	print_file("/tmp/bullshit");
}

void	heredoc_statement_execute(char **command_statement, struct minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("FORK ERROR");
	if (!pid)
		execute_heredoc(command_statement);
	else
		wait(NULL);
}

void	minishell_process_command(struct ast *ast, struct minishell *minishell)
{
	char 	**command_statement;
	char	*command_path;

	command_statement = command_statement_create(ast);
	command_path = get_path(command_statement[0], minishell->env);
	if (ast->value.token_type == COMMAND)
		command_statement_execute(command_statement, command_path, minishell);
	else if (ast->value.token_type == LESS)
		less_statement_execute(command_statement, minishell);
	else
		heredoc_statement_execute(command_statement, minishell);
	command_statement_destroy(command_statement);
}

void	minishell_process_bool(struct ast *ast, struct minishell *minshell)
{
	if (ast->value.token_type == TRUE)
		write(1, "0\n", 2);
	else
		write(1, "1\n", 2);
}

void	minishell_ast_execute(struct ast *ast, struct minishell *minishell)
{
	struct ast *tmp;

	tmp = ast;
	if (!ast)
		return ;
	if (ast->value.token_type == COMMAND
		|| ast->value.token_type == DOUBLE_SMALLER
		|| ast->value.token_type == LESS)
		minishell_process_command(ast, minishell);
	else if (ast->value.token_type == FALSE
		|| ast->value.token_type == TRUE)
		minishell_process_bool(ast, minishell);
	else if (ast->value.token_type == PIPE)
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