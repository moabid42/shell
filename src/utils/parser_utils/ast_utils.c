/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:16:16 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 23:17:09 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_child(int root, struct token_stream *tmp)
{
	if (tmp->token_type < DOUBLE_SMALLER)
		return (false);
	if (tmp->token_type == PIPE && root == EQUAL)
		return (true);
	if (tmp->token_type > root)
		return (true);
	return (false);
}

struct ast	*ast_lookup(struct ast *node, char *token_name)
{
	if (my_strcmp(node->value.token_name, token_name) == 0)
		return (node);
	if (node->left)
		if (ast_lookup(node->left, token_name) != NULL)
			return (ast_lookup(node->left, token_name));
	return(NULL);
}

struct ast *find_prev(struct ast *node, char *token_name)
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

bool	ast_not_right_type(struct ast *ast)
{
	return (ast->value.token_type == COMMAND 
	|| ast->value.token_type == DOUBLE_SMALLER
	|| ast->value.token_type == LESS
	|| ast->value.token_type == PIPE
	|| ast->value.token_type == ANDAND
	|| ast->value.token_type == OROR
	|| ast->value.token_type == TRUE
	|| ast->value.token_type == FALSE
	|| ast->value.token_type == GREATER
	|| ast->value.token_type == DOUBLE_GREATER
	|| ast->value.token_type == EQUAL
	|| is_builtin(ast->value.token_name)
	|| !my_strcmp(ast->value.token_name, "exit"));
}

bool	ast_is_assign(struct ast *ast)
{
	return (ast->value.token_type == EQUAL
		|| !my_strcmp(ast->value.token_name, "export"));
}