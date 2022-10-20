/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:33:39 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 22:13:04 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

bool syntax_analyzer_create(struct token_stream *token_stream, struct ast *ast, struct minishell *minishell)
{
	struct ast *tmp;
	struct token_stream *iterator;

	tmp = ast;
	iterator = token_stream;
	if (iterator->token_type < 3)
	{
		minishell->return_value = 258;
		dprintf(2, "esh: syntax error near unexpected token `%s'\n", iterator->token_name);
		return (false);
	}
	if (ast->value.token_type < 5 && ast->right == NULL && minishell->handled == false)
	{
		minishell->return_value = 258;
		dprintf(2, "esh: syntax error near unexpected token `%s'\n", tmp->value.token_name);
		return (false);
	}
	return (true);
}
