/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:59 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 21:57:53 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "parser.h"
#include "utils.h"

struct ast	*ast_create_first_node(struct minishell *minishell, struct token_stream *token_stream)
{
	struct ast	*tmp;

	tmp = ft_malloc(sizeof(struct ast));
	if (token_stream->token_type == VARIABLE)
	{
		tmp->value.token_name = minishell_find_variable(minishell, token_stream->token_name);
		tmp->value.token_type = WORD;
		if (tmp->value.token_name == NULL)
			tmp->value.token_name = ft_strdup("");
	}	
	else
	{
		tmp->value.token_name = token_stream->token_name;
		tmp->value.token_type = token_stream->token_type;
	}
	if (tmp->value.token_type == WORD || tmp->value.token_type == VARIABLE)
	{
		if (ft_iscommand(tmp->value.token_name, minishell->env) == true
			|| ft_isexecutable(tmp->value.token_name) == true)
			tmp->value.token_type = COMMAND;
		else if (is_builtin(tmp->value.token_name) == true
			|| !my_strcmp(tmp->value.token_name, "exit"))
			tmp->value.token_type = BUILTIN;
	}
	tmp->isroot = true;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

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

//create a function that looks for a char inside the binary tree
struct ast *find_prev(struct ast *node, char *token_name)
{
	// printf("We are in the node : %s\n", token_name);
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

struct ast *ast_create_subtree(struct minishell *minishell, struct token_stream **prev, struct token_stream **stream)
{
	struct ast *ast;

	if (!my_strcmp((*stream)->token_name, "(")
		|| !my_strcmp((*stream)->token_name, ")"))
	{
		(*stream) = (*stream)->next;
		minishell->index_flag *= 2;
		minishell->brakets_flag |= minishell->index_flag;
	}
	ast = ast_create_first_node(minishell, *stream);
	*prev = *stream;
	*stream = (*stream)->next;
	while (*stream)
	{
		if (!my_strcmp((*stream)->token_name, "(")
			|| !my_strcmp((*stream)->token_name, ")"))
		{
			(*stream) = (*stream)->next;
			minishell->index_flag *= 2;
			minishell->brakets_flag |= minishell->index_flag;
			continue ;
		}
		if ((*stream)->token_type == ANDAND || (*stream)->token_type == OROR)
			return(ast);
		if (is_child(ast->value.token_type, *stream) == true)
			ast_insert_child(node_create_child(*stream, minishell, (*prev)->token_type), &ast, (*prev), minishell);
		else
			ast_insert_parent(node_create_parent((*stream)), &ast, minishell);
		*prev = *stream;
		(*stream) = (*stream)->next;
	}
	if (ast_not_right_type(ast) == false)
	{
		minishell->return_value = 127;
		if (!ft_isalnum(ast->value.token_name[0]))
			;
		else if (ast->left)
			dprintf(2, "esh: %s: command not found ...\n", ast->left->value.token_name);
		else
			dprintf(2, "esh: %s: command not found ...\n", ast->value.token_name);
		minishell->handled = true;
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
	char       			export_fg;
		
	tmp = token_stream;
	prev = tmp;
	if (!my_strcmp(tmp->token_name, "(")
		|| !my_strcmp(tmp->token_name, ")"))
		tmp = tmp->next;
	ast = ast_create_first_node(minishell, tmp);
	tmp = tmp->next;
	while (tmp)
	{
		if (!my_strcmp(tmp->token_name, "(")
			|| !my_strcmp(tmp->token_name, ")"))
		{
			tmp = tmp->next;
			continue;
		}
		if (!my_strcmp(prev->token_name, "export"))
			export_fg = true;
		if (prev->token_type == ANDAND || prev->token_type == OROR)
		{
			if (ast_is_assign(ast->left) == true)
				minishell_ast_execute(ast->left, minishell);
			ast->right = ast_create_subtree(minishell, &prev, &tmp);
			if (!tmp || !ast->right)
				break;
		}
		if (export_fg == false && prev->token_type == EQUAL
			&& tmp->token_type != ANDAND
			&& tmp->token_type != OROR
			&& tmp->token_type != EQUAL)
		{
			ast->right = ast_create_subtree(minishell, &prev, &tmp);
			if (!tmp || !ast->right)
				break;
		}
		if (is_child(ast->value.token_type, tmp) == true)
			ast_insert_child(node_create_child(tmp, minishell, prev->token_type), &ast, prev, minishell);
		else
			ast_insert_parent(node_create_parent(tmp), &ast, minishell);
		prev = tmp;
		if (tmp)
			tmp = tmp->next;
		else
			break;
	}
	// structure(ast, 0);
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