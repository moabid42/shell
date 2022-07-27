/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:59 by moabid            #+#    #+#             */
/*   Updated: 2022/07/26 18:42:18 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

// bool	is_instring(struct token_stream *stream, char *token)
// {
// 	while (stream)
// 	{
// 		if (stream->token_type == DOUBLE_QUOTES 
// 			|| stream->token_type == SINGLE_QUOTES)
// 			return (true);
// 		stream = stream->next;
// 	}
// 	return (false);
// }

// bool	is_child(struct token_stream *tmp)
// {
// 	struct token_stream *iterator;

// 	iterator = tmp;
// 	while (iterator)
// 	{
// 		if (iterator->token_type == SPACE && is_instring(tmp, iterator->token_name) == false);
// 			iterator = iterator->next;
		
// 		iterator = iterator->next;
// 	}
	

// 	return (false);
// }

struct ast *semantic_analyzer_create(struct minishell *minishell, struct scripts *script)
{
	// struct ast *ast;
	// struct token_stream *tmp;
		
	// tmp = script->token_stream;
	// ast = ft_malloc(sizeof(struct ast));
	// while (script->tmp)
	// {
	// 	if (is_child(script->token_stream) == true)
	// 		node_create_child(&ast, script->token_stream);
	// 	else
	// 		node_create_parent(&ast, script->token_stream);
	// 	tmp = tmp->next;
	// }
	// return (ast);
}

void semantic_analyzer_destroy(struct minishell *minishell) {

}