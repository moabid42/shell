/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_run_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:27:07 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:25:07 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**command_statement_create(struct s_ast *ast)
{
	int			i;
	struct s_ast	*tmp;
	char		**command_statement;

	i = 0;
	tmp = ast;
	command_statement = ft_malloc(sizeof(char *) * (child_n_c(ast) + 2));
	if (tmp->value.token_name[0] == '.' && tmp->value.token_name[1] == '/')
		command_statement[i] = ft_strdup(tmp->value.token_name + 2);
	else
		command_statement[i] = ft_strdup(tmp->value.token_name);
	if (tmp->left)
		command_statement[++i] = ft_strdup(tmp->left->value.token_name);
	command_statement = duplicate_right_left(tmp, &i, command_statement);
	command_statement[child_n_c(ast) + 1] = NULL;
	return (command_statement);
}

void	command_statement_execute(char **command_statement, char *path,
	struct s_minishell *minishell, int fd_out)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		ft_error("FORK ERROR");
	if (!pid)
	{
		dup2(fd_out, 1);
		correct_args(command_statement, minishell);
		if (is_builtin(command_statement[0]) == true)
			builtin_run(command_statement, minishell);
		else if (execve(path, command_statement, e_to_s(minishell->env)) == -1)
			perror("esh ");
		exit(127);
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

char	*get_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path;
	t_env	*head;
	int		i;

	head = env;
	while (head && ft_strnstr(head->name, "PATH", 4) == 0)
		head = head->next;
	if (!head)
		return (NULL);
	paths = ft_split(head->content, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = parser(cmd, paths[i]);
		if (path)
			return (path);
		i++;
	}
	freeme(paths);
	return (NULL);
}

bool	a_err(struct s_minishell *m, char *var, int value)
{
	m->return_value = value;
	dprintf(2, "esh: %s: command not found .\n", var);
	return (true);
}

void	command_run(char **command_statement, char *command_path,
				struct s_minishell *m, struct s_ast *ast)
{
	if (ast->value.token_type == DOUBLE_SMALLER)
		heredoc_statement_execute(ast, m, m->fd_out);
	else if (ast->value.token_type == COMMAND
		|| (ast->left && ast->left->value.token_type == COMMAND)
		|| ast->value.token_type == BUILTIN)
		command_statement_execute(command_statement, command_path,
			m, m->fd_out);
	else if (ast->left->value.token_type == LESS)
		less_statement_execute(command_statement, ast->left, m, m->fd_out);
	else if (ast->value.token_type == LESS)
		less_statement_execute(command_statement, ast, m, m->fd_out);
	else if (ast->value.token_type == GREATER
		|| ast->value.token_type == DOUBLE_GREATER)
		a_err(m, ast->value.token_name, 127);
}
