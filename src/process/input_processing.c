/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:14:03 by moabid            #+#    #+#             */
/*   Updated: 2022/07/17 00:59:06 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

// bool	minishell_input_parse(struct minishell *minishell, struct input *input)
// {
// 	if (minishell->variable == false)
// 		input->minishell->variables = NULL;
// 	else
// 		input->minishell->variables = input_save_variables(minishell, input);
		
// }

// bool	input_ast_create(struct input *input, struct ast *ast)
// {
	
// }

void	minishell_process_input(struct minishell *minishell)
{
	struct token_stream token_stream;
	struct syntax_tree	syntax_tree;
	struct ast			ast;

	lexical_analyzer_create(minishell, &token_stream);
	syntax_analyzer_create(&token_stream, &syntax_tree);
	semantic_analyzer_create(&syntax_tree, &ast);
	// minishell_ast_execute(&ast);
	// semantic_analyzer_destroy(&ast);
	// syntax_analyzer_destroy(&syntax_tree);
	// lexical_analyzer_destroy(&token_stream);
	return ;
}