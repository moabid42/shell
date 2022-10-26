/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:16:16 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 13:19:49 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_child(int root, struct s_token_stream *tmp)
{
	if (tmp->token_type < DOUBLE_SMALLER)
		return (false);
	if (tmp->token_type == PIPE && root == EQUAL)
		return (true);
	if (tmp->token_type > root)
		return (true);
	return (false);
}

struct s_ast	*ast_lookup(struct s_ast *node, char *token_name)
{
	if (my_strcmp(node->value.token_name, token_name) == 0)
		return (node);
	if (node->left)
		if (ast_lookup(node->left, token_name) != NULL)
			return (ast_lookup(node->left, token_name));
	return (NULL);
}

struct s_ast	*find_prev(struct s_ast *node, char *token_name)
{
	if (my_strcmp(node->value.token_name, token_name) == 0)
	{
		if (node->left)
		{
			if (ast_lookup(node->left, token_name) == NULL)
				return (node);
		}
		else
			return (node);
	}
	if (node->right)
		if (find_prev(node->right, token_name) != NULL)
			return (find_prev(node->right, token_name));
	if (node->left)
		if (find_prev(node->left, token_name) != NULL)
			return (find_prev(node->left, token_name));
	return (NULL);
}

bool	ast_not_right_type(struct s_ast *ast)
{
	return (ast->value.token_type == COMMAND
		|| ast->value.token_type == DOUBLE_SMALLER
		|| ast->value.token_type == LESS
		|| ast->value.token_type == PIPE
		|| ast->value.token_type == AND
		|| ast->value.token_type == OR
		|| ast->value.token_type == TRUE
		|| ast->value.token_type == FALSE
		|| ast->value.token_type == GREATER
		|| ast->value.token_type == DOUBLE_GREATER
		|| ast->value.token_type == EQUAL
		|| is_builtin(ast->value.token_name)
		|| !my_strcmp(ast->value.token_name, "exit"));
}

bool	ast_is_assign(struct s_ast *ast)
{
	return (ast->value.token_type == EQUAL
		|| !my_strcmp(ast->value.token_name, "export"));
}
