/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:59 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 10:23:09 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "parser.h"

struct s_ast	*sub_tree_builder(struct s_ast *ast,
		struct s_minishell *minishell,
		struct s_token_stream **prev, struct s_token_stream **stm)
{
	*prev = *stm;
	*stm = (*stm)->next;
	while (*stm)
	{
		if (is_bracket(minishell, (*stm)->token_name) == true
			|| (*stm)->token_type == AND || (*stm)->token_type == OR)
		{
			(*stm) = (*stm)->next;
			continue ;
		}
		else
			return (ast);
		if (is_child(ast->value.token_type, *stm) == true)
			ast_insert_child(node_create_child(*stm, minishell,
					(*prev)->token_type), &ast, (*prev), minishell);
		else
			ast_insert_parent(node_create_parent((*stm)), &ast, minishell);
		*prev = *stm;
		(*stm) = (*stm)->next;
	}
	return (NULL);
}

struct s_ast	*ast_create_subtree(struct s_minishell *minishell,
		struct s_token_stream **prev, struct s_token_stream **stm)
{
	struct s_ast	*ast;

	ast = check_bracket_and_assign(minishell, stm);
	ast = sub_tree_builder(ast, minishell, prev, stm);
	if (ast != NULL)
		return (ast);
	if (ast_not_right_type(ast) == false)
		return (handle_not_right(minishell, ast));
	if (ast_is_assign(ast) == true)
		minishell_ast_execute(ast, minishell);
	return (ast);
}

struct s_ast	*assign_child(struct s_ast *ast, struct s_token_stream *prev,
		struct s_token_stream *tmp, struct s_minishell *minishell)
{
	if (is_child(ast->value.token_type, tmp) == true)
		ast_insert_child(node_create_child(tmp, minishell,
				prev->token_type), &ast, prev, minishell);
	else
		ast_insert_parent(node_create_parent(tmp), &ast, minishell);
	return (ast);
}

struct s_ast	*tree_builder(struct s_minishell *m, struct s_ast *ast,
			struct s_token_stream *p, struct s_token_stream *tmp)
{
	while (tmp)
	{
		if (a_right(ast, m) || is_bracket(m, tmp->token_name))
		{
			tmp = tmp->next;
			continue ;
		}
		if (export(m, p) || p->token_type == AND || p->token_type == OR)
		{
			if (ast_is_assign(ast->left) == true)
				minishell_ast_execute(ast->left, m);
			ast->right = ast_create_subtree(m, &p, &tmp);
			if (!tmp || !ast->right)
				break ;
		}
		if (is_sub_tree(m->export_fg, p, tmp))
		{
			ast->right = ast_create_subtree(m, &p, &tmp);
			if (!tmp || !ast->right)
				break ;
		}
		ast = assign_child(ast, p, tmp, m);
		advance(&p, &tmp);
	}
	return (ast);
}

struct s_ast	*semantic_analyzer_create(struct s_minishell *minishell,
			struct s_token_stream *token_stream)
{
	struct s_ast			*ast;
	struct s_token_stream	*tmp;
	struct s_token_stream	*prev;

	tmp = token_stream;
	prev = tmp;
	minishell->start_right = false;
	minishell->export_fg = 0;
	while (is_bracket(minishell, tmp->token_name) == true)
		tmp = tmp->next;
	ast = ast_create_first_node(minishell, tmp);
	tmp = tmp->next;
	ast = tree_builder(minishell, ast, prev, tmp);
	if (minishell->open != 0)
		return (error_exit_null(minishell, ERROR_B, NULL, 258));
	if (ast_not_right_type(ast) == false)
		return (handle_not_right_2(minishell, ast));
	return (ast);
}
