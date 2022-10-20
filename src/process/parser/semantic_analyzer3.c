/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:27:36 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 22:08:31 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "parser.h"
#include "utils.h"

void	print_tree(struct s_ast *node)
{
	static int	level;

	if (node->left)
		print_tree(node->left);
	if (node->right)
		print_tree(node->right);
	if (node->isroot == true)
	{
		printf("The root is : [%s][%d]\n", node->value.token_name, level);
		level++;
	}
	else
	{
		printf("[%s] LEVEL : %d\n", node->value.token_name, level);
		level++;
	}
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

struct s_ast	*find_end_right(structs s_ast *node)
{
	if (!node->right)
		return (node);
	node = node->right;
	while (node->left)
		node = node->left;
	return (node);
}

void	ast_insert_child(struct s_ast *node, \
		struct s_ast **ast, struct s_token_stream *prev, \
		struct s_minishell *minishell)
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
		iterator = find_prev(iterator, prev_token);
		if (iterator->left == NULL)
			iterator->left = node;
		else if (iterator->right == NULL)
			iterator->right = node;
	}
}
