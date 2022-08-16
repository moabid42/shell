/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:59 by moabid            #+#    #+#             */
/*   Updated: 2022/08/16 15:49:50 by moabid           ###   ########.fr       */
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
	// printf("This token type is : %d of %s and the prev is : %d\n", tmp->token_type, tmp->token_name, prev_type);
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


// bool	search_tree(struct ast *node, char *token_name)
// {
// 	if (node->value.token_name == token_name)
// 		return (true);
// 	if (node->left)
// 		if (search_tree(node->left, token_name) == true)
// 			return (true);
// 	if (node->right)
// 		if (search_tree(node->right, token_name) == true)
// 			return (true);
// 	return (false);
// }
//create a function that looks for a char inside the binary tree
struct ast *find_prev(struct ast *node, char *token_name)
{
	if (my_strcmp(node->value.token_name, token_name) == 0)
		return (node);
	if (node->right)
		if (find_prev(node->right, token_name) != NULL)
			return (find_prev(node->right, token_name));
	if (node->left)
		if (find_prev(node->left, token_name) != NULL)
			return (find_prev(node->left, token_name));
	return (NULL);
}


void	ast_insert_child(struct ast *node, struct ast **ast, struct token_stream *prev)
{
	struct ast *iterator;

	iterator = *ast;
	if (iterator->left == NULL)
		iterator->left = node;
	else if (iterator->right == NULL)
		iterator->right = node;
	else
	{
		iterator = find_prev(iterator, prev->token_name);
		// printf("We foudn the prev token %s\n", iterator->value.token_name);
		if (iterator->left == NULL)
			iterator->left = node;
		else if (iterator->right == NULL)
			iterator->right = node;
	}
	// else
	// {
	// 	while (iterator->left != NULL)
	// 		iterator = iterator->left;
	// 	iterator->left = node;
	// }
	// To Do : implement for any number of childs
	// if (!iterator)
	// 	return ;
	// if (my_strcmp(token->token_name, iterator->value.token_name) == 0)
	// {
	// 	if (iterator->left == NULL)
	// 		iterator->left = node;
	// 	else if (iterator->right == NULL)
	// 		iterator->right = node;
	// }
	// else if (iterator->value.token_type < token->token_type)
	// 	ast_insert_child(node, &iterator->left, token);
	// else if (iterator->value.token_type > token->token_type)
	// 	ast_insert_child(node, &iterator->right, token);
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
struct ast	*node_create_child(struct token_stream *tmp, struct minishell *minishell)
{
	struct ast *node;

	node = ft_malloc(sizeof(struct ast));
	if (node_contain_special(tmp->token_name, '\"') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\"', ft_strlen(tmp->token_name) - 1);
	else if (node_contain_special(tmp->token_name, '\'') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\'', ft_strlen(tmp->token_name) - 1);
	else if (node_contain_special_single(tmp->token_name, '\\') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\\', ft_strlen(tmp->token_name));	
	else
		node->value.token_name = tmp->token_name;
	node->value.token_type = tmp->token_type;
	if (node->value.token_type == WORD)
	{
		if (ft_iscommand(node->value.token_name, minishell->env) == true)
			node->value.token_type = COMMAND;
		else if (ft_isfile(node->value.token_name) == true)
			node->value.token_type = FILES;
	}
	node->isroot = false;
	node->left = NULL;
	node->right = NULL;
	return (node);
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
	|| ast->value.token_type == DOUBLE_GREATER);
}

void padding ( char ch, int n )
{
  int i;

  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void structure ( struct ast *root, int level )
{
  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    structure ( root->right, level + 1 );
    padding ( '\t', level );
    printf ( "%s\n", root->value.token_name );
    structure ( root->left, level + 1 );
  }
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
			ast_insert_child(node_create_child(tmp, minishell), &ast, prev);
		else
			node_create_parent(tmp, &ast);
		prev = tmp;	
		tmp = tmp->next;
	}
	structure(ast, 0);
	if (ast_not_right_type(ast) == false)
		ft_error("Error : AST not right root type");
	return (ast);
}

void semantic_analyzer_destroy(struct minishell *minishell) {

}