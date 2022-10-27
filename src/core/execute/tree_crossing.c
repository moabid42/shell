/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_crossing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:36:31 by moabid            #+#    #+#             */
/*   Updated: 2022/10/27 16:32:20 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

/// Number of childs complex 
int	child_n_c(struct s_ast *node)
{
	int				num;
	struct s_ast	*tmp;

	num = 0;
	tmp = node;
	if (tmp->left)
		num++;
	if (tmp->right || tmp->left)
	{
		if (tmp->right)
		{
			num++;
			tmp = tmp->right;
		}
		else
			tmp = tmp->left;
		while (tmp->left)
		{
			num++;
			tmp = tmp->left;
		}
	}
	return (num);
}

char	**duplicate_right_left(struct s_ast *tmp, int *i, char **cmds)
{
	if (tmp->right)
	{
		cmds[++(*i)] = ft_strdup(tmp->right->value.token_name);
		tmp = tmp->right;
		while (tmp->left)
		{
			cmds[++(*i)] = ft_strdup(tmp->left->value.token_name);
			tmp = tmp->left;
		}
	}
	else if (tmp->left)
	{
		tmp = tmp->left;
		while (tmp->left)
		{
			cmds[++(*i)] = ft_strdup(tmp->left->value.token_name);
			tmp = tmp->left;
		}
	}
	return (cmds);
}

void	command_statement_destroy(char **command_statement)
{
	int	i;

	i = 0;
	while (command_statement[i])
	{
		free(command_statement[i]);
		i++;
	}
	free(command_statement);
}

void	correct_args(char **cmds, struct s_minishell *minishell)
{
	int	i;

	i = 0;
	if (!my_strcmp(cmds[0], "cat"))
	{
		cmds[1] = ft_strjoin(cmds[1], cmds[2]);
		cmds[2] = NULL;
	}
}

int	minishell_ast_execute(struct s_ast *ast, struct s_minishell *minishell)
{
	struct s_ast	*tmp;

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
}
