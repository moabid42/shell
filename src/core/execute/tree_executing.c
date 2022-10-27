/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_executing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:36:12 by moabid            #+#    #+#             */
/*   Updated: 2022/10/27 01:58:20 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_statement_run(char **command_statement,
	char *command_path, struct s_minishell *minishell)
{
	if (is_builtin(command_statement[0]) == true)
		builtin_run(command_statement, minishell);
	if (execve(command_path, command_statement, e_to_s(minishell->env)) == -1)
		ft_error(command_statement[0]);
}

char	**command_statement_create_complexe(struct s_ast *ast)
{
	int				i;
	struct s_ast	*tmp;
	char			**command_statement;

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

void	command_statement_execute_complexe(struct s_ast *ast,
	struct s_minishell *minishell)
{
	char	**command_statement;
	char	*command_path;

	command_statement = command_statement_create_complexe(ast);
	command_path = get_path(command_statement[0], minishell->env);
	command_statement_run(command_statement, command_path, minishell);
	command_statement_destroy(command_statement);
}

void	redirection_run(struct s_ast *ast, struct s_ast *first,
	struct s_minishell *minishell, int fd_out)
{
	if (ast->left->value.token_type == PIPE)
		redirection_run(ast->left, first, minishell, fd_out);
	if (ast->left->value.token_type != PIPE)
		process_pipe_run_left(ast, minishell);
	if (ast->right != first->right)
		process_pipe_run_right(ast, minishell);
	else
		minishell_ast_execute(ast->right, minishell);
}
