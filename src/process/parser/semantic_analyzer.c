/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:59 by moabid            #+#    #+#             */
/*   Updated: 2022/09/19 17:16:23 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "parser.h"
#include "utils.h"

char	*find_return_expend(struct minishell *minishell, char return_var)
{
	if (return_var == '?')
		return (ft_itoa(minishell->return_value));
	// else if (return_var == '_')
	// 	return ()
	return (NULL);
}

char	*minishell_find_variable(struct minishell *minishell, char *variable)
{
	struct s_variable	*iterator;
	char				*expend_var;
	t_env				*tmp;
	int					i;

	iterator = minishell->variables;
	expend_var = "!?_";
	tmp = minishell->env;
	i = 0;
	while (iterator)
	{
		if (my_strcmp(iterator->var, variable + 1) == 0)
			return (iterator->value);
		iterator = iterator->next;
	}
	while (tmp)
	{
		if (!my_strcmp(tmp->name, variable + 1))
			return (tmp->content);
		tmp = tmp->next;
	}
	while(expend_var[i])
	{
		if (variable[1] == expend_var[i])
			return (find_return_expend(minishell, expend_var[i]));
		i++;
	}
	return (NULL);
}

struct ast	*ast_create_first_node(struct minishell *minishell, struct token_stream *token_stream)
{
	struct ast	*tmp;

	tmp = ft_malloc(sizeof(struct ast));
	if (token_stream->token_type == VARIABLE)
	{
		tmp->value.token_name = minishell_find_variable(minishell, token_stream->token_name);
		tmp->value.token_type = WORD;
		if (tmp->value.token_name == NULL)
			write(2, "Error: variable not found ,. ,", 26);
	}	
	else
	{
		tmp->value.token_name = token_stream->token_name;
		tmp->value.token_type = token_stream->token_type;
	}
	if (tmp->value.token_type == WORD || tmp->value.token_type == VARIABLE)
	{		
		if (ft_iscommand(tmp->value.token_name, minishell->env) == true)
			tmp->value.token_type = COMMAND;
		else if (is_builtin(tmp->value.token_name) == true
			|| !my_strcmp(tmp->value.token_name, "exit"))
			tmp->value.token_type = BUILTIN;
	}
	tmp->isroot = true;
	tmp->left = NULL;
	tmp->right = NULL;
	// printf("The token name is %s and the type is %d\n", tmp->value.token_name, tmp->value.token_type);
	return (tmp);
}

//check if the node is a child of the previous node
bool	is_child(int root, struct token_stream *tmp)
{
	// printf("This token type is : %d of %s and the prev is : %d\n", tmp->token_type, tmp->token_name, prev_type);
	if (tmp->token_type < DOUBLE_SMALLER)
		return (false);
	if (tmp->token_type > root)
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

struct ast	*ast_lookup(struct ast *node, char *token_name)
{
	if (my_strcmp(node->value.token_name, token_name) == 0)
		return (node);
	if (node->left)
		if (ast_lookup(node->left, token_name) != NULL)
			return (ast_lookup(node->left, token_name));
	return(NULL);
}

//create a function that looks for a char inside the binary tree
struct ast *find_prev(struct ast *node, char *token_name)
{
	// printf("We are in the node : %s\n", node->value.token_name);
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

struct ast *find_end_right(struct ast *node)
{
	if (!node->right)
		return(node);
	node = node->right;
	while(node->left)
		node = node->left;
	return (node);
}

void	ast_insert_child(struct ast *node, struct ast **ast, struct token_stream *prev, struct minishell *minishell)
{
	struct ast	*iterator;
	char		*prev_token;

	// printf("We are gonna add the chid [%s][%d]\n", node->value.token_name, node->value.token_type);
	iterator = *ast;
	prev_token = prev->token_name;
	if (iterator->left == NULL)
		iterator->left = node;
	else if (iterator->right == NULL)
		iterator->right = node;
	else
	{
		// printf("We foudn the prev token %s\n", prev->token_name);
		if (prev->token_type == VARIABLE)
			prev_token = minishell_find_variable(minishell, prev->token_name);
		iterator = find_prev(iterator, prev_token);
		if (iterator->left == NULL)
			iterator->left = node;
		else if (iterator->right == NULL)
			iterator->right = node;
	}
}

//create a parent node
struct ast	*node_create_parent(struct token_stream *tmp)
{
	struct ast *node;

	node = ft_malloc(sizeof(struct ast));
	node->value.token_name = tmp->token_name;
	node->value.token_type = tmp->token_type;
	node->isroot = false;
	node->left = NULL;
	node->right = NULL;
	// *child = node;
	return (node);
}

void	ast_insert_parent(struct ast *node, struct ast **root)
{
	struct ast *tmp;

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

//create a child node
struct ast	*node_create_child(struct token_stream *tmp, struct minishell *minishell, int prev_type)
{
	struct ast *node;

	node = ft_malloc(sizeof(struct ast));
	if (node_contain_special(tmp->token_name, '\"') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\"', ft_strlen(tmp->token_name) - 1);
	else if (node_contain_special(tmp->token_name, '\'') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\'', ft_strlen(tmp->token_name) - 1);
	else if (node_contain_special_single(tmp->token_name, '\\') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\\', ft_strlen(tmp->token_name));	
	else if (tmp->token_type == VARIABLE)
	{
		// printf("We are looking for %s", tmp->token_name);
		node->value.token_name = minishell_find_variable(minishell, tmp->token_name);
		if (node->value.token_name == NULL)
			write(2, "Error: variable not found . . .", 26);
	}
	else
		node->value.token_name = tmp->token_name;
	node->value.token_type = tmp->token_type;
	if (node->value.token_type == WORD
		|| node->value.token_type == VARIABLE)
	{
		if (ft_iscommand(node->value.token_name, minishell->env) == true
			&& prev_type < GREATER)
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
	|| ast->value.token_type == DOUBLE_GREATER
	|| ast->value.token_type == EQUAL
	|| is_builtin(ast->value.token_name)
	|| !my_strcmp(ast->value.token_name, "exit"));
}

void padding ( char ch, int n )
{
  int i;

  for (i = 0; i < n; i++)
    putchar(ch);
}

void structure ( struct ast *root, int level )
{
  if (root == NULL)
  {
    padding('\t', level );
    puts("~");
  }
  else
  {
    structure(root->right, level + 1 );
    padding('\t', level);
    printf("%s[%d]\n", root->value.token_name, root->value.token_type);
    structure(root->left, level + 1);
  }
}

bool	ast_is_assign(struct ast *ast)
{
	return (ast->value.token_type == EQUAL
		|| !my_strcmp(ast->value.token_name, "export"));
}

struct ast *ast_create_subtree(struct minishell *minishell, struct token_stream **prev, struct token_stream **stream)
{
	struct ast *ast;
		
	ast = ast_create_first_node(minishell, *stream);
	*prev = *stream;
	*stream = (*stream)->next;
	while (*stream)
	{
		if ((*stream)->token_type == ANDAND || (*stream)->token_type == OROR)
			return(ast);
		if (is_child(ast->value.token_type, *stream) == true)
			ast_insert_child(node_create_child(*stream, minishell, (*prev)->token_type), &ast, (*prev), minishell);
		else
			ast_insert_parent(node_create_parent((*stream)), &ast);
		*prev = *stream;
		(*stream) = (*stream)->next;
	}
	// structure(ast, 0);
	if (ast_not_right_type(ast) == false)
	{
		minishell->return_value = 127;
		dprintf(2, "esh: %s: command not found ...\n", ast->left->value.token_name);
		return (NULL);
	}
	if (ast_is_assign(ast) == true)
		minishell_ast_execute(ast, minishell);
	return (ast);
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
		if (prev->token_type == ANDAND || prev->token_type == OROR)
		{
			if (ast_is_assign(ast->left) == true)
				minishell_ast_execute(ast->left, minishell);
			ast->right = ast_create_subtree(minishell, &prev, &tmp);
			if (!tmp || !ast->right)
				break;
		}
		if (is_child(ast->value.token_type, tmp) == true)
			ast_insert_child(node_create_child(tmp, minishell, prev->token_type), &ast, prev, minishell);
		else
			ast_insert_parent(node_create_parent(tmp), &ast);
		prev = tmp;
		if (tmp)
			tmp = tmp->next;
		else
			break;
	}
	if (ast_not_right_type(ast) == false)
	{
		minishell->return_value = 127;
		if (!ast->left)
			dprintf(2, "esh: %s: command not found ..\n", ast->value.token_name);
		else
			dprintf(2, "esh: %s: command not found ..\n", ast->left->value.token_name);
		return (NULL);
	}
	return (ast);
}

void semantic_analyzer_destroy(struct minishell *minishell) {

}