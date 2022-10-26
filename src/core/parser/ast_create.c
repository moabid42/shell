/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:56:17 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 13:21:24 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_sanitize(struct s_ast *node, struct s_token_stream *tmp,
	struct s_minishell *minishell)
{
	if (node_contain_special(tmp->token_name, '\"') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\"',
				ft_strlen(tmp->token_name) - 1);
	else if (node_contain_special(tmp->token_name, '\'') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\'',
				ft_strlen(tmp->token_name) - 1);
	else if (node_contain_special_single(tmp->token_name, '\\') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\\',
				ft_strlen(tmp->token_name));
	else if (tmp->token_type == VARIABLE)
	{
		node->value.token_name = minishell_find_variable(minishell,
				tmp->token_name);
		if (node->value.token_name == NULL)
			node->value.token_name = ft_strdup("");
	}
	else
		node->value.token_name = tmp->token_name;
}

struct s_ast	*node_create_child(struct s_token_stream *tmp,
			struct s_minishell
	*minishell, int prev_type)
{
	struct s_ast	*node;

	node = ft_malloc(sizeof(struct s_ast));
	child_sanitize(node, tmp, minishell);
	node->value.token_type = tmp->token_type;
	if (node->value.token_type == WORD
		|| node->value.token_type == VARIABLE)
	{
		if (ft_iscommand(node->value.token_name, minishell->env) == true
			&& (prev_type < GREATER || prev_type == EQUAL))
			node->value.token_type = COMMAND;
		else if (ft_isfile(node->value.token_name) == true)
			node->value.token_type = FILES;
	}
	node->isroot = false;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	ast_insert_child(struct s_ast *node, struct s_ast **ast,
	struct s_token_stream *prev, struct s_minishell *minishell)
{
	struct s_ast	*iterator;
	char			*prev_token;

	iterator = *ast;
	prev_token = prev->token_name;
	if (iterator->left == NULL)
		iterator->left = node;
	else if (iterator->right == NULL)
		iterator->right = node;
	else
	{
		if (prev->token_type == VARIABLE)
			prev_token = minishell_find_variable(minishell, prev->token_name);
		if (prev_token == NULL)
			prev_token = ft_strdup("");
		if (prev_token[0] == '\"')
			prev_token = ft_special_trim(prev_token, '\"',
					ft_strlen(prev_token));
		iterator = find_prev(iterator->right, prev_token);
		if (iterator->left == NULL)
			iterator->left = node;
		else if (iterator->right == NULL)
			iterator->right = node;
	}
}

//////////////////////// PARENT ////////////////////////

struct s_ast	*node_create_parent(struct s_token_stream *tmp)
{
	struct s_ast	*node;

	node = ft_malloc(sizeof(struct s_ast));
	node->value.token_name = tmp->token_name;
	node->value.token_type = tmp->token_type;
	node->isroot = false;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	ast_insert_parent(struct s_ast *node, struct s_ast **root,
		struct s_minishell *minishell)
{
	struct s_ast	*tmp;

	tmp = (*root)->right;
	if (node->value.token_type <= (*root)->value.token_type
		|| ((node->value.token_type / 2 == 0)
			&& (node->value.token_type / 2 == 0)))
	{
		node->isroot = true;
		node->left = *root;
		*root = node;
	}
	else
	{
		(*root)->right = node;
		node->left = tmp;
	}
}
