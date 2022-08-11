/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_crossing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:36:31 by moabid            #+#    #+#             */
/*   Updated: 2022/08/11 18:13:34 by moabid           ###   ########.fr       */
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

void	minishell_process_command(struct ast *ast, struct minishell *minishell)
{
	char 	**command_statement;
	char	*command_path;

	command_statement = command_statement_create(ast);
	command_path = get_path(command_statement[0], minishell->env);
	command_statement_execute(command_statement, command_path, minishell);
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
	if (ast->value.token_type == COMMAND)
		minishell_process_command(ast, minishell);
	else if (ast->value.token_type == FALSE
		|| ast->value.token_type == TRUE)
		minishell_process_bool(ast, minishell);
	else if (ast->value.token_type == PIPE)
		minishell_process_pipeline(tmp, minishell);
	// else if (ast->value.token_type == DOUBLE_SMALLER)
	// 	minishell_process_heredoc(ast, minishell);
	// // else if (ast->value.token_type == LESS)
	// else if (ast->value.token_type == ANDAND
	// 	|| ast->value.token_type == OROR)
	// 	minishell_process_and_or(ast, minishell);
	// else if (ast->value.token_type == AST_SUBSHELL)
	// 	minishell_process_subshell(ast, minishell);
	// else if (ast->value.token_type == AST_COMMAND_LIST)
	// 	minishell_process_command_list(ast, minishell);
}