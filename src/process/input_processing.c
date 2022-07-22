/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:14:03 by moabid            #+#    #+#             */
/*   Updated: 2022/07/19 18:40:15 by moabid           ###   ########.fr       */
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

// void	minishell_process_input(struct minishell *minishell)
// {
// 	lexical_analyzer_create(minishell);
// 	syntax_analyzer_create(minishell);
// 	semantic_analyzer_create(minishell);
// 	// minishell_ast_execute(&ast);
// 	semantic_analyzer_destroy(minishell);
// 	syntax_analyzer_destroy(minishell);
// 	lexical_analyzer_destroy(minishell);
// 	return ;
// }

void	minishell_process_input(struct scripts *script)
{
	struct token_stream token_stream;

	if (script)
		return ;
	printf("We are creating a token_stream for : %s\n", script->input_line);
	lexical_analyzer_create(&token_stream, script);
	// syntax_analyzer_create(minishell);
	// semantic_analyzer_create(minishell);
	// minishell_ast_execute(&ast);
	minishell_process_input(script->next);
}

void	minishell_destroy_input(struct scripts *script)
{
	if (script)
		return ;
	// semantic_analyzer_destroy(token_stream, script);
	// syntax_analyzer_destroy(minishell);
	lexical_analyzer_destroy(&script->token_stream);
	minishell_destroy_input(script->next);
}

void	minishell_read_input(struct minishell *minishell)
{
	struct	scripts *tmp_cr;
	struct	scripts *tmp_ds;
	
	tmp_cr = minishell->scripts;
	tmp_ds = minishell->scripts;
	if (!minishell_scripts_parse(minishell))
		ft_error(UNEXPECTED_TOKEN);
	printf("]]]]]]      %s\n", tmp_cr->input_line);
	printf("[[[[]]]]       %s\n", scripts_line[1]);
	minishell_process_input(tmp_cr);
	minishell_destroy_input(tmp_ds);
}