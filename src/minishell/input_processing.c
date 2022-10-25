/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:14:03 by moabid            #+#    #+#             */
/*   Updated: 2022/10/25 04:39:42 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

void	minishell_ast_execute_subshells(struct ast *ast,
	struct minishell *minishell)
{
	if (ast->left->value.token_type < 2)
		minishell_ast_execute_subshells(ast->left, minishell);
	if (ast->left->value.token_type > 1)
		minishell->return_value = minishell_ast_execute(ast->left, minishell);
	if (minishell->return_value == 0 && ast->value.token_type == 0)
		minishell->return_value &= minishell_ast_execute(ast->right, minishell);
	else if (minishell->return_value != 0 && ast->value.token_type == 1)
		minishell->return_value = minishell_ast_execute(ast->right, minishell);
}

void	syntax_analyzer_run(struct ast *ast, struct minishell *minishell,
	struct token_stream *token_stream)
{
	if (ast != NULL)
	{
		if (syntax_analyzer_create(token_stream, ast, minishell) == true)
		{
			if (ast && ast->value.token_type < 2)
				minishell_ast_execute_subshells(ast, minishell);
			else
				minishell->return_value = minishell_ast_execute(ast, minishell);
		}
	}
}

void	minishell_process_input(struct scripts *script,
	struct minishell *minishell)
{
	struct token_stream	*token_stream;
	struct ast			*ast;

	if (!script)
		return ;
	minishell->handled = false;
	if (is_weirdo(script->input_line, minishell) == true)
		return ;
	else
	{
		token_stream = lexical_analyzer_create(script, minishell);
		if (token_stream == NULL)
			return ;
		minishell->open = 0;
		ast = semantic_analyzer_create(minishell, token_stream);
		syntax_analyzer_run(ast, minishell, token_stream);
	}
	minishell_process_input(script->next, minishell);
}

void	minishell_destroy_input(struct scripts *script)
{
	if (!script)
		return ;
	minishell_destroy_input(script->next);
}

void	minishell_read_input(struct minishell *minishell)
{
	struct scripts	*tmp_cr;
	struct scripts	*tmp_ds;

	signal(SIGINT, SIG_IGN);
	if (!minishell_scripts_parse(minishell))
		return ;
	tmp_cr = minishell->scripts;
	minishell_process_input(tmp_cr, minishell);
	minishell->brakets_flag = 0;
	minishell->index_flag = 1;
	tmp_ds = minishell->scripts;
	minishell_destroy_input(tmp_ds);
}
