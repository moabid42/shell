/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_crossing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:36:31 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 17:49:35 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

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
	else if (tmp->left)
	{
		tmp = tmp->left;
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
	// dprintf(2, "The number of the childs not complexe is : %d for %s\n", ast_child_num_complexe(ast) + 1, tmp->value.token_name);
	if (tmp->value.token_name[0] == '.'
		&& tmp->value.token_name[1] == '/')
		command_statement[i] = ft_strdup(tmp->value.token_name + 2);
	else
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
	else if (tmp->left)
	{
		tmp = tmp->left;
		while (tmp->left)
		{
			command_statement[++i] = ft_strdup(tmp->left->value.token_name);
			tmp = tmp->left;
		}
	}
	command_statement[ast_child_num_complexe(ast) + 1] = NULL;
	// printer_split(command_statement);
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
	int 	status;

	status = 0;
	pid = fork();
	if (pid == -1)
		ft_error("FORK ERROR");
	if (!pid)
	{
		dup2(fd_out, 1);
		// dprintf(2, "The path is : %s\n", path);
		if(is_builtin(command_statement[0]) == true)
			builtin_run(command_statement, minishell);
		// else if (access(path, X_OK) != 0)
		// {
		// 	perror("esh ");
		// 	exit(127);
		// }
		else if (execve(path, command_statement, env_to_string(minishell->env)) == -1)
			perror("esh ");
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
	// printf("The status is %d\n", status);
	if (status == 32512)
		minishell->return_value = 127;
	else if (status != 0)
		minishell->return_value = 1;
	else
		minishell->return_value = 0;
	// printf("The return status is : %d of %s\n", minishell->return_value, command_statement[0]);
}

int	openfile(char *file, int re_or_wr)
{
	int	ret;

	if (re_or_wr == 0)
	{
		ret = open(file, O_RDONLY, 0777);
		if (access(file, F_OK | R_OK) != 0)
		{
			dprintf(2, "esh: no such file or directory: %s\n", file);
			return (-1);
		}
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

void	less_statement_execute(char **command_statement, struct ast *ast, struct minishell *minishell, int fd_out)
{
	pid_t	pid;
	int		fd_in;

	fd_in = openfile(command_statement[1], 0);
	if (fd_in == -1)
	{
		dprintf(2, "esh: %s: No such file or directory\n", ast->left->value.token_name);
		exit(1);
	}
	if (ast->right == NULL)
		;
	else
	{
		pid = fork();
		if (pid == -1)
			ft_error("FORK ERROR");
		if (!pid)
		{
			dup2(fd_out, 1);
			dup2(fd_in, 0);
			command_statement_execute_complexe(ast->right, minishell);
		}
		else
			wait(NULL);
	}
	close(fd_in);
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
		if (line == NULL)
			break;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_out);
		free(line);
	}
}

void	heredoc_execute_caller(struct ast *tmp, int direction)
{
	if (tmp->left->value.token_type == DOUBLE_SMALLER)
		heredoc_execute_caller(tmp->left, direction);
	if (tmp->left->value.token_type != DOUBLE_SMALLER)
	{
		if (direction == 0)
			execute_heredoc(tmp->left->value.token_name, 0);
		else
			execute_heredoc(tmp->right->value.token_name, 0);
		return ;
	}
	else
		execute_heredoc(tmp->right->value.token_name, 1);
}

void	heredoc_forward_command(struct ast *ast, struct minishell *minishell)
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

struct ast *ast_seek_end(struct ast *ast)
{
	if (ast->value.token_type == COMMAND || ast->left == NULL)
		return (ast);
	else
		return (ast_seek_end(ast->left));
}

void	heredoc_statement_execute(struct ast *ast, struct minishell *minishell)
{
	struct ast	*tmp;
	struct ast	*end;

	tmp = ast;
	end = ast_seek_end(tmp);
	if (end->value.token_type == COMMAND)
		heredoc_execute_caller(tmp, RIGHT);
	else
		heredoc_execute_caller(tmp, LEFT);
	if (end->value.token_type == COMMAND)
		heredoc_forward_command(end, minishell);
	else
		print_file("/tmp/bullshit");
}

void	minishell_process_command(struct ast *ast, struct minishell *minishell)
{
	int		fd_out;
	struct ast	*jump;
	char 	**command_statement;
	char	*command_path;

	jump = ast;
	if (ast->value.token_type == WORD)
	{
		minishell->return_value = 127;
		dprintf(2, "esh: %s: command not found .\n", ast->value.token_name);
		return ;
	}
	if (ast->value.token_type == GREATER)
	{
		if (ast->right == NULL)
			return ;
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
	// printf("command_statement[0] = %s\n", command_statement[0]);
	if (ft_strchr(jump->value.token_name, '/') != NULL)
		command_path = ft_strdup(jump->value.token_name);
	else
		command_path = get_path(command_statement[0], minishell->env);
	// printf("command_path = %s\n", command_path);
	if (command_path == NULL)
		command_path = jump->value.token_name;
	// printer_split(command_statement);
	if (ast->value.token_type == DOUBLE_SMALLER)
		heredoc_statement_execute(ast, minishell);
	else if (ast->value.token_type == COMMAND
		|| (ast->left && ast->left->value.token_type == COMMAND)
		|| ast->value.token_type == BUILTIN)
		command_statement_execute(command_statement, command_path, minishell, fd_out);
	else if (ast->left->value.token_type == LESS)
		less_statement_execute(command_statement, ast->left, minishell, fd_out);
	else if (ast->value.token_type == LESS)
		less_statement_execute(command_statement, ast, minishell, fd_out);
	else if (ast->value.token_type == GREATER
		|| ast->value.token_type == DOUBLE_GREATER)
	{
		minishell->return_value = 127;
		dprintf(2, "esh: %s: command not found\n", ast->value.token_name);
	}
	command_statement_destroy(command_statement);
}

void	minishell_process_bool(struct ast *ast, struct minishell *minishell)
{
	if (ast->value.token_type == FALSE)
		minishell->return_value = 1;
	else
		minishell->return_value = 0;
}

bool	ast_is_simple(struct ast *ast)
{
	if (ast->value.token_type == COMMAND
		|| ast->value.token_type == DOUBLE_SMALLER
		|| ast->value.token_type == LESS
		|| (ast->value.token_type == GREATER
		&& ast->left->value.token_type != PIPE)
		|| (ast->value.token_type == DOUBLE_GREATER
		&& ast->left->value.token_type != PIPE)
		|| is_builtin(ast->value.token_name) == true)
		return (true);
	return (false);
}

struct s_variable *variable_create(char **variable_list)
{
	struct s_variable *variable;

	variable = ft_malloc(sizeof(struct s_variable));
	variable->var = variable_list[0];
	variable->value = variable_list[1];
	variable->next = NULL;
	return (variable);
}

//create a function that will insert a node in the end of the list
void	variable_insert_node(struct s_variable *variable, struct s_variable *list)
{
	while (list)
	{
		// printf("We are checking %s and %s\n", list->var, variable->var);
		if (!my_strcmp(list->var, variable->var))
		{
			list->value = variable->value;
			return ;
		}
		if (list->next)
			list = list->next;
		else
			break;
	}
	list->next = variable;
}

bool	minishell_var_lookup(char *var_str, struct s_variable *variable)
{
	char **var_list;
	
	var_list = ft_split(var_str, '=');
	while (variable)
	{
		if (!my_strcmp(variable->var, var_list[0])
			&& !my_strcmp(variable->value, var_list[1]))
		{
			free_split(var_list);
			return (true);
		}
		variable = variable->next;
	}
	free_split(var_list);
	return (false);
}

void	minishell_save_variable(char *variable_assigned, struct minishell *minishell)
{
	char **variable_list;
	struct s_variable *new;
	
	if (minishell_var_lookup(variable_assigned, minishell->variables) == true)
		return ;
	variable_list = ft_split(variable_assigned, '=');
	// printf("We are gonna save the variable with %s and %s\n", variable_list[0], variable_list[1]);
	if (!minishell->variables)
		minishell->variables = variable_create(variable_list);
	else
	{
		new = variable_create(variable_list);
		variable_insert_node(new, minishell->variables);
	}
	// printer_variable(minishell->variables);
}

void	printer_variable(struct s_variable *variable)
{
	struct s_variable *tmp;

	tmp = variable;
	while (tmp)
	{
		printf("We have %s = %s\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
}

// void	prepare_exit(struct ast *ast, struct minishell *minishell)
// {
// 	char		**argv;

// 	argv = command_statement_create(ast);
// 	ft_exit(argv, minishell);
// }

void	builtin_run_ast(struct ast *ast, struct minishell *minishell)
{
	char	**cmd_list;

	cmd_list = command_statement_create(ast);
	if (!my_strcmp(cmd_list[0], "exit"))
	 	ft_exit(cmd_list, minishell);
	else if(!my_strcmp(cmd_list[0], "cd"))
		ft_cd(cmd_list, minishell);
	else if(!my_strcmp(cmd_list[0], "export"))
		ft_export(cmd_list, minishell);
	else if(!my_strcmp(cmd_list[0], "unset"))
		ft_unset(cmd_list, minishell);
}

bool	is_builtin_ast(char *cmd)
{
	return (!my_strcmp(cmd, "export")
		|| !my_strcmp(cmd, "cd")
		|| !my_strcmp(cmd, "exit")
		|| !my_strcmp(cmd, "unset"));
}

void	minishell_run_equal(struct ast *ast, struct minishell *minishell)
{
	minishell_save_variable(ast->value.token_name, minishell);
	if (ast->right)
		minishell_ast_execute(ast->right, minishell);
	else
		minishell_ast_execute(ast->left, minishell);
}

int	minishell_ast_execute(struct ast *ast, struct minishell *minishell)
{
	struct ast *tmp;

	// printf("We are processing : %s\n", ast->value.token_name);
	tmp = ast;
	if (!ast)
		return (minishell->return_value);
	else if (is_builtin_ast(ast->value.token_name) == true)
		builtin_run_ast(ast, minishell);
	else if (ast->value.token_type == EQUAL)
		minishell_run_equal(ast, minishell);
	else if (ast_is_simple(ast) == true)
		minishell_process_command(ast, minishell);
	else if (ast->value.token_type == FALSE
		|| ast->value.token_type == TRUE)
		minishell_process_bool(ast, minishell);
	else if (ast->value.token_type == PIPE
		|| ast->value.token_type == GREATER
		|| ast->value.token_type == DOUBLE_GREATER)
		minishell_process_pipeline(tmp, minishell);
	else
	{
		minishell->return_value = 127;
		dprintf(2, "esh: %s: command not found .....\n", ast->value.token_name);
	}
	ast->value.exit_status = minishell->return_value;	
	return (minishell->return_value);
	// printf("The return value is : %d for %s\n", minishell->return_value, ast->value.token_name);
}