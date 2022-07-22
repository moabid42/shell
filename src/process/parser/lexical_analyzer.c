/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:22 by moabid            #+#    #+#             */
/*   Updated: 2022/07/19 18:38:40 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

bool	minishell_scripts_parse(struct minishell *minishell)
{
	char	**scripts_line;
	int		i;

	i = 0;
	scripts_line = ft_split(minishell->input_str, ';');
	// printf("]]]]]]      %s\n", scripts_line[0]);
	// printf("[[[[]]]]       %s\n", scripts_line[1]);
	minishell->scripts_num = ft_get_nb_strs(minishell->input_str, ';');
	if (minishell->scripts_num == 1)
		minishell->scripts = ft_create_node_script(scripts_line[0]);
	else
		minishell->scripts = ft_create_stack_scripts(scripts_line, minishell->scripts_num);
	free_split(scripts_line);
	if (minishell->scripts == NULL)
		return (false);
	return (true);
}

void	lexical_analyzer_create(struct token_stream *token_stream, struct scripts *script)
{
	char				**tokens;

	tokens = ft_split_tokens(script);
	script->tokens_num = get_nb_tokens(script->input_line);
	token_stream = ft_create_stack_tkstream(tokens, script->tokens_num);
	script->token_stream = token_stream;
	printer_token(token_stream);
}

// void	lexical_analyzer_create(struct minishell *minishell)
// {
// 	if (!minishell_scripts_parse(minishell))
// 		ft_error(UNEXPECTED_TOKEN);
// 	token_stream_create(minishell);
// 	exit(0);
// }

void	minishell_scripts_destroy(struct minishell *minishell)
{
	
}

void	lexical_analyzer_destroy(struct token_stream **token_stream)
{
	struct token_stream *tmp;

	tmp = *token_stream;
	while (tmp)
	{
		garbage_collect_token(tmp);
		tmp = tmp->next;
	}
	*token_stream = NULL;
}