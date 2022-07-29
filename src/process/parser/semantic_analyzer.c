/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:59 by moabid            #+#    #+#             */
/*   Updated: 2022/07/29 18:13:05 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

// bool	is_instring(struct token_stream *stream, char *token)
// {
// 	while (stream)
// 	{
// 		if (stream->token_type == DOUBLE_QUOTES 
// 			|| stream->token_type == SINGLE_QUOTES)
// 			return (true);
// 		stream = stream->next;
// 	}
// 	return (false);
// }

// struct ast	*ast_create_first_node(struct minishell *minishell, struct token_stream *token_stream)
// {
// 	struct ast	*tmp;

// 	tmp = ft_malloc(sizeof(struct ast));
// 	tmp->value.token_name = token_stream->token_name;
// 	tmp->value.token_type = token_stream->token_type;
// 	if (tmp->value.token_type == WORD)
// 		if (ft_iscommand(tmp->value.token_name, minishell->env) == true)
// 			tmp->value.token_type = COMMAND;
// 	tmp->isroot = true;
// 	tmp->left = NULL;
// 	tmp->right = NULL;
// 	return (tmp);
// }

// struct ast	*node_create_child(struct token_stream *tmp)
// {
// 	struct ast *node;

// 	node = ft_malloc(sizeof(struct ast));
// 	node->value.token_name = tmp->token_name;
// 	node->value.token_type = tmp->token_type;
// 	if (node->value.token_type == WORD)
// 		if (ft_isfile(node->value.token_name) == true)
// 			node->value.token_type = FILES;
// 	node->isroot = false;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// struct ast 	*node_create_parent(struct ast *node, struct ast **child)
// {
// 	struct ast *node;

// 	node = ft_malloc(sizeof(struct ast));
// 	node->value.token_name = tmp->token_name;
// 	node->value.token_type = tmp->token_type;
// 	node->isroot = true;
// 	node->left = *child;
// 	node->right = NULL;
// 	return (node);
// }

// create the first node of the ast
struct ast	*ast_create_first_node(struct minishell *minishell, struct token_stream *token_stream)
{
	struct ast	*tmp;

	tmp = ft_malloc(sizeof(struct ast));
	tmp->value.token_name = token_stream->token_name;
	tmp->value.token_type = token_stream->token_type;
	if (tmp->value.token_type == WORD)
		if (ft_iscommand(tmp->value.token_name, minishell->env) == true)
			tmp->value.token_type = COMMAND;
	tmp->isroot = true;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

//check if the node is a child of the previous node
bool	is_child(int prev_type, struct token_stream *tmp)
{
	if (tmp->token_type >= prev_type)
		return (true);
	return (false);
}

//create a function that prints a binary tree
void	print_tree(struct ast *node)
{
	static int level = 0;

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

void	ast_insert_child(struct ast *node, struct ast **ast)
{
	struct ast *iterator;

	iterator = *ast;
	if (iterator->left == NULL)
		iterator->left = node;
	else if (iterator->right == NULL)
		iterator->right = node;
	// To Do : implement for any number of childs
}

//create a parent node
void	node_create_parent(struct token_stream *tmp, struct ast **child)
{
	struct ast *node;

	node = ft_malloc(sizeof(struct ast));
	node->value.token_name = tmp->token_name;
	node->value.token_type = tmp->token_type;
	node->isroot = true;
	node->left = *child;
	node->right = NULL;
	*child = node;
}

//create a child node
struct ast	*node_create_child(struct token_stream *tmp)
{
	struct ast *node;

	node = ft_malloc(sizeof(struct ast));
	node->value.token_name = tmp->token_name;
	node->value.token_type = tmp->token_type;
	if (node->value.token_type == WORD)
		if (ft_isfile(node->value.token_name) == true)
			node->value.token_type = FILES;
	node->isroot = false;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

struct ast *semantic_analyzer_create(struct minishell *minishell, struct token_stream *token_stream)
{
	struct ast *ast;
	struct token_stream *tmp;
	struct token_stream *prev;
		
	tmp = token_stream;
	prev = tmp;
	ast = ast_create_first_node(minishell, tmp);
	tmp = tmp->next;
	while (tmp)
	{
		if (is_child(prev->token_type, tmp) == true)
		{
			ast_insert_child(node_create_child(tmp), &ast);
		}
		else
			node_create_parent(tmp, &ast);
		tmp = tmp->next;
	}
	print_tree(ast);
	return (ast);
}

void semantic_analyzer_destroy(struct minishell *minishell) {

}