/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:59 by moabid            #+#    #+#             */
/*   Updated: 2022/10/25 21:36:20 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "parser.h"

struct ast	*check_bracket_and_assign(struct minishell *minishell,
		struct token_stream **stm)
{
	if (is_bracket(minishell, (*stm)->token_name) == true)
		(*stm) = (*stm)->next;
	return (ast_create_first_node(minishell, *stm));
}

struct ast	*ast_create_subtree(struct minishell *minishell,
		struct token_stream **prev, struct token_stream **stm)
{
	struct ast	*ast;

	ast = check_bracket_and_assign(minishell, stm);
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
	if (ast_not_right_type(ast) == false)
		return (handle_not_right(minishell, ast));
	if (ast_is_assign(ast) == true)
		minishell_ast_execute(ast, minishell);
	return (ast);
}

struct ast	*semantic_analyzer_create(struct minishell *minishell,
			struct token_stream *token_stream)
{
	struct ast			*ast;
	struct token_stream	*tmp;
	struct token_stream	*prev;
	char				export_fg;

	tmp = token_stream;
	prev = tmp;
	minishell->start_right = false;
	while (is_bracket(minishell, tmp->token_name) == true)
		tmp = tmp->next;
	ast = ast_create_first_node(minishell, tmp);
	tmp = tmp->next;
	while (tmp)
	{
		if (ast->value.token_type == 5)
			minishell->start_right = true;
		if (is_bracket(minishell, tmp->token_name) == true)
		{
			tmp = tmp->next;
			continue ;
		}
		if (!my_strcmp(prev->token_name, "export"))
			export_fg = true;
		if (prev->token_type == AND || prev->token_type == OR)
		{
			if (ast_is_assign(ast->left) == true)
				minishell_ast_execute(ast->left, minishell);
			ast->right = ast_create_subtree(minishell, &prev, &tmp);
			if (!tmp || !ast->right)
				break ;
		}
		if (is_sub_tree(export_fg, prev, tmp))
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
		tmp = tmp->next;
	}
	if (minishell->open != 0)
	{
		error_exit(minishell, "esh: syntax error near unexpected token \
			')'\n", NULL, 258);
		return (NULL);
	}
	if (ast_not_right_type(ast) == false)
		return (handle_not_right_2(minishell, ast));
	return (ast);
}

void	semantic_analyzer_destroy(struct minishell *minishell)
{
}
