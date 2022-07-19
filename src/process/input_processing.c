/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:14:03 by moabid            #+#    #+#             */
/*   Updated: 2022/07/19 11:26:43 by moabid           ###   ########.fr       */
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
	struct syntax_stream	syntax_stream;
	struct ast				ast;

	lexical_analyzer_create(minishell);
	syntax_analyzer_create(minishell, &syntax_stream);
	semantic_analyzer_create(&syntax_stream, &ast);
	// minishell_ast_execute(&ast);
	semantic_analyzer_destroy(minishell);
	syntax_analyzer_destroy(minishell);
	lexical_analyzer_destroy(minishell);
	return ;
}
