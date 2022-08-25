/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:22 by moabid            #+#    #+#             */
/*   Updated: 2022/08/25 15:17:09 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

void	print_tokens(char **scripts_line, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		printf("The token value is : %s\n", scripts_line[i]);
		i++;
	}
}

bool minishell_scripts_parse(struct minishell *minishell)
{
	char	**scripts_line;


	scripts_line = ft_new_split(minishell->input_str, ';', "\"'");
	// print_tokens(scripts_line, words_count(minishell->input_str, ';', "\"'"));
	// printf("The number of elem: %d\n", words_count(minishell->input_str, ';', "\"'") );
	minishell->scripts_num = words_count(minishell->input_str, ';', "\"'");
	// }
	if (minishell->scripts_num == 1)
		minishell->scripts = ft_create_node_script(scripts_line[0]);
	else
		minishell->scripts = ft_create_stack_scripts(scripts_line, minishell->scripts_num);
	free_split(scripts_line);
	if (minishell->scripts == NULL)
		return (false);
	return (true);
}

void	printer_split(char **tokens)
{
	while(*tokens)
	{
		dprintf(2, "The token is : %s\n", *tokens);
		tokens++;
	}
}

struct token_stream *lexical_analyzer_create(struct scripts *script, struct minishell *minishell)
{
	char **tokens;
	struct token_stream *token_stream;

	tokens = ft_new_split(script->input_line, ' ', "\"'");
	script->tokens_num = words_count(script->input_line, ' ', "\"'");
	// printf("The number of tokens: %d\n", words_count(script->input_line, ';', "\"'") );
	// printer_split(tokens);
	token_stream = ft_create_stack_tkstream(minishell, tokens, script->tokens_num);
	// printer_token(token_stream);
	script->token_stream = token_stream;
	return (token_stream);
}

void minishell_scripts_destroy(struct minishell *minishell) {

}

void lexical_analyzer_destroy(struct token_stream **token_stream) {
	struct token_stream *tmp;

	tmp = *token_stream;
	while (tmp) {
		garbage_collect_token(tmp);
		tmp = tmp->next;
	}
	*token_stream = NULL;
}