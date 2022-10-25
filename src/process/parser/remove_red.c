/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:04:16 by moabid            #+#    #+#             */
/*   Updated: 2022/10/25 16:10:50 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	have_multi_redi(struct token_stream *token_stream)
{
	while (token_stream)
	{
		if (token_stream->token_name[0] == '>' && token_stream->next
			&& token_stream->next->next
			&& token_stream->next->next->token_name[0] == '>')
			return (true);
		token_stream = token_stream->next;
	}
	return (false);
}

void	node_remove(struct token_stream *prev, struct token_stream *next,
					struct token_stream *iter)
{
	openfile(next->token_name, 1);
	free(next);
	free(iter);
}

void	token_stream_remove(struct token_stream **token_stream)
{
	struct token_stream	*iter;
	struct token_stream	*next;
	struct token_stream	*prev;

	iter = *token_stream;
	prev = iter;
	next = iter->next;
	while (iter)
	{
		if (iter->token_name[0] == '>' && iter->next
			&& iter->next->next
			&& iter->next->next->token_name[0] == '>')
		{
			prev->next = next->next;
			node_remove(prev, next, iter);
			iter = prev->next;
			if (iter)
				next = iter->next;
			continue ;
		}
		prev = iter;
		iter = iter->next;
		if (iter)
			next = iter->next;
	}
}
