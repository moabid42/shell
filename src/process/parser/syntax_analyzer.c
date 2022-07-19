/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:33:39 by moabid            #+#    #+#             */
/*   Updated: 2022/07/19 12:45:06 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

void	token_stream_tokenize(struct token_stream *token_stream)
{
	
}

void	syntax_analyzer_create(struct minishell *minishell)
{
	int	i;
	struct scripts *tmp;

	i = 0;
	tmp = minishell->scripts;
	while (i < minishell->scripts_num)
	{
		token_stream_tokenize(tmp->token_stream);
		tmp = tmp->next;
	}
}

void	syntax_analyzer_destroy(struct minishell *minishell)
{
	
}