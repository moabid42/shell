/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:59 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 00:43:45 by frame            ###   ########.fr       */
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

static struct minishell	*semantic_analyzer_helper(struct s_data *d)
{
	while (d->tmp)
	{
		if (d->ast->value.token_type == 5)
			d->ms->start_right = true;
		if (is_bracket(d->ms, d->tmp->token_name) == true)
		{
			d->tmp = d->tmp->next;
			continue ;
		}
		if (!my_strcmp(d->prev->token_name, "export"))
			d->export_fg = true;
		if (d->prev->token_type == AND || d->prev->token_type == OR)
		{
			if (ast_is_assign(d->ast->left) == true)
				minishell_ast_execute(d->ast->left, d->ms);
			d->ast->right = ast_create_subtree(d->ms, &d->prev, &d->tmp);
			if (!d->tmp || !d->ast->right)
				break ;
		}
		if (is_sub_tree(d->export_fg, d->prev, d->tmp))
		{
			d->ast->right = ast_create_subtree(d->ms, &d->prev, &d->tmp);
			if (!d->tmp || !d->ast->right)
				break ;
		}
		if (is_child(d->ast->value.token_type, d->tmp) == true)
			ast_insert_child(node_create_child(d->tmp, d->ms,
					d->prev->token_type), &d->ast, d->prev, d->ms);
		else
			ast_insert_parent(node_create_parent(d->tmp), &d->ast, d->ms);
		d->prev = d->tmp;
		d->tmp = d->tmp->next;
	}
	return (d->ms);
}

struct	s_data
{
	struct token_stream	*t_s;
	struct ast			*ast;
	struct token_stream	*tmp;
	struct token_stream	*prev;
	struct minishell	*ms;
	char				export_fg;
};

struct s_data	s_data_init(struct minishell *minishell,
			struct token_stream *token_stream)
{
	struct s_data	d;

	d.t_s = token_stream;
	d.tmp = token_stream;
	d.prev = d.tmp;
}

struct ast	*semantic_analyzer_create(struct minishell *minishell,
			struct token_stream *token_stream)
{
	struct s_data	d;

	d = s_data_init(minishell, token_stream);
	d.ms->start_right = false;
	while (is_bracket(d.ms, d.tmp->token_name) == true)
		d.tmp = d.tmp->next;
	d.ast = ast_create_first_node(d.ms, d.tmp);
	d.tmp = d.tmp->next;
	d.ms = semantic_analyzer_helper(&d);
	if (d.ms->open != 0)
	{
		error_exit(d.ms, "esh: syntax error near unexpected token \
			')'\n", NULL, 258);
		return (NULL);
	}
	if (ast_not_right_type(d.ast) == false)
		return (handle_not_right_2(d.ms, d.ast));
	return (d.ast);
}

// void	semantic_analyzer_destroy(struct minishell *minishell)
// {
// }
