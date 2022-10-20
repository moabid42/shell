/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:14:03 by moabid            #+#    #+#             */
/*   Updated: 2022/10/20 01:31:12 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

void	minishell_ast_execute_subshells(struct ast *ast, struct minishell *minishell)
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

void decToBinary(long long n)
{
    int binaryNum[64];
	int	count = 0;
    int i = 0;

    while (n > 0)
	{
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
	{
		count++;
        printf("%d", binaryNum[j]);
	}
}

void minishell_process_input(struct scripts *script, struct minishell *minishell)
{
	struct token_stream *token_stream;
	struct ast *ast;

	if (!script)
		return;
	// printf("We are creating a token_stream for : %s\n", script->input_line);
	minishell->handled = false;
	if (!my_strcmp(script->input_line, "<<")
		|| !my_strcmp(script->input_line, "<>")
		|| !my_strcmp(script->input_line, "<")
		|| !ft_strncmp(script->input_line, "<> &&", 5))
	{
		minishell->return_value = 258;
		dprintf(2, "minishell: syntax error near unexpected token `newline'");
	}
	else
	{
		token_stream = lexical_analyzer_create(script, minishell);
		ast = semantic_analyzer_create(minishell, script->token_stream);
		// structure(ast, 0);
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
	minishell_process_input(script->next, minishell);
}

void minishell_destroy_input(struct scripts *script)
{
	if (!script)
		return;
	// semantic_analyzer_destroy(token_stream, script);
	// syntax_analyzer_destroy(minishell);
	lexical_analyzer_destroy(&script->token_stream);
	minishell_destroy_input(script->next);
}

void minishell_read_input(struct minishell *minishell)
{
	struct scripts *tmp_cr;
	struct scripts *tmp_ds;

	signal(SIGINT, SIG_IGN);
	if (!minishell_scripts_parse(minishell))
		ft_error(UNEXPECTED_TOKEN);
	tmp_cr = minishell->scripts;
	minishell_process_input(tmp_cr, minishell);
	minishell->brakets_flag = 0;
	minishell->index_flag = 1;
	tmp_ds = minishell->scripts;
	minishell_destroy_input(tmp_ds);
}