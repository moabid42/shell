/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:22 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 15:10:44 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

struct token_stream	*lexical_analyzer_create(
		struct scripts *script, struct minishell *minishell)
{
	char					**tokens;
	struct s_token_stream	*token_stream;
	t_args					args;

	args.split_char = " ";
	args.single_word = (char *[]){"(", ")", "||", "&&", "|",
		"&&", "<<", ">>", "<", ">", NULL};
	args.ignore = (char *)"\\";
	args.ign_char_inside = (char *)"\"'";
	tokens = ft_reader(script->input_line, &args);
	script->tokens_num = reader_word_count(script->input_line, &args);
	if (star_exist(tokens) == true)
	{
		tokens = token_expend_star(tokens, script->tokens_num - 1);
		script->tokens_num = count_tokens(tokens);
	}
	token_stream = ft_create_stack_tkstream(
			minishell, tokens, script->tokens_num);
	script->token_stream = token_stream;
	return (token_stream);
}

/*
void minishell_scripts_destroy(struct minishell *minishell){}
*/
void	lexical_analyzer_destroy(struct token_stream **token_stream)
{
	struct s_token_stream	*tmp;

	tmp = *token_stream;
	while (tmp)
	{
		garbage_collect_token(tmp);
		tmp = tmp->next;
	}
	*token_stream = NULL;
}
