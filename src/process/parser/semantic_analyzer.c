/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:59 by moabid            #+#    #+#             */
/*   Updated: 2022/07/28 00:19:02 by moabid           ###   ########.fr       */
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
	
// 	return (false);
// }

// struct ast	*ast_create_first_node(struct token_stream *token_stream)
// {
// 	struct ast	*tmp;

// 	tmp = ft_malloc(sizeof(struct ast));
// 	tmp->value.token_name = token_stream->token_name;
// 	tmp->value.token_type = token_stream->token_type;
// 	if (tmp->value.token_type == WORD)
// 	{
// 		if (ft_iscommand(tmp->value.token_name) == true)
// 			tmp->value.token_type == COMMAND;
// 		else if (ft_isfile() == true)
// 			tmp->value.token_type == FILE;
// 	}
// 	tmp->isroot = true;
// 	tmp->left == NULL;
// 	tmp->right == NULL;
// 	return (tmp);
// }


struct ast *semantic_analyzer_create(struct minishell *minishell, struct scripts *script)
{
	// struct ast *ast;
	// struct token_stream *tmp;
		
	// tmp = script->token_stream;
	// ast = ast_create_firstnode(minishell, tmp);
	// tmp = tmp->next;
	// while (tmp)
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