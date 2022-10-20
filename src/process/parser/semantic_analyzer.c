/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:59 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 16:21:14 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "parser.h"
#include "utils.h"

void	structure(struct s_ast *root, int level)
{
	if (root == NULL)
	{
		padding('\t', level);
		puts("~");
	}
	else
	{
		structure(root->right, level + 1);
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

struct s_ast	*ast_create_subtree(struct s_minishell *minishell,
		struct s_token_stream **prev, struct s_token_stream **stream)
{
	struct s_ast	*ast;

	if (!my_strcmp((*stream)->token_name, "(") \
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
		if (!my_strcmp((*stream)->token_name, "(") \
			|| !my_strcmp((*stream)->token_name, ")"))
		{
			(*stream) = (*stream)->next;
			minishell->index_flag *= 2;
			minishell->brakets_flag |= minishell->index_flag;
			continue ;
		}
		if ((*stream)->token_type == ANDAND || (*stream)->token_type == OROR)
			return (ast);
		if (is_child(ast->value.token_type, *stream) == true)
			ast_insert_child(node_create_child(
					*stream, minishell, (*prev)->token_type), \
						&ast, (*prev), minishell);
		else
			ast_insert_parent(node_create_parent((*stream)), &ast, minishell);
		*prev = *stream;
		(*stream) = (*stream)->next;
	}
	if (ast_not_right_type(ast) == false)
	{
		minishell->return_value = 127;
		dprintf(2, "esh: %s: command not found ...\n", \
			ast->left->value.token_name);
		return (NULL);
	}
	if (ast_is_assign(ast) == true)
		minishell_ast_execute(ast, minishell);
	return (ast);
}

struct s_ast	*semantic_analyzer_create( \
		struct s_minishell *minishell, struct s_token_stream *token_stream)
{
	struct s_ast			*ast;
	struct s_token_stream	*tmp;
	struct s_token_stream	*prev;
	char					export_fg;

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
			minishell->index_flag *= 2;
			minishell->brakets_flag |= minishell->index_flag;
			continue ;
		}
		if (!my_strcmp(prev->token_name, "export"))
			export_fg = true;
		if (prev->token_type == ANDAND || prev->token_type == OROR)
		{
			minishell->index_flag *= 2;
			if (ast_is_assign(ast->left) == true)
				minishell_ast_execute(ast->left, minishell);
			ast->right = ast_create_subtree(minishell, &prev, &tmp);
			if (!tmp || !ast->right)
				break ;
		}
		if (export_fg == false && prev->token_type == EQUAL
			&& tmp->token_type != ANDAND
			&& tmp->token_type != OROR
			&& tmp->token_type != EQUAL)
		{
			ast->right = ast_create_subtree(minishell, &prev, &tmp);
			if (!tmp || !ast->right)
				break ;
		}
		if (is_child(ast->value.token_type, tmp) == true)
			ast_insert_child(node_create_child(tmp, minishell,
					prev->token_type), &ast, prev, minishell);
		else
			ast_insert_parent(node_create_parent(tmp), &ast, minishell);
		prev = tmp;
		if (tmp)
			tmp = tmp->next;
		else
			break ;
	}
	// structure(ast, 0);
	if (ast_not_right_type(ast) == false)
	{
		minishell->return_value = 127;
		if (!ast->left)
			dprintf(2, "esh: %s: command not found ..\n", ast->value.token_name);
		else
			dprintf(2, "esh: %s: command not found ..\n",
				ast->left->value.token_name);
		return (NULL);
	}
	return (ast);
}
/*
void semantic_analyzer_destroy(struct minishell *minishell)
{
	
}
*/