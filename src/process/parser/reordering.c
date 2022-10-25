/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reordering.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 04:55:44 by moabid            #+#    #+#             */
/*   Updated: 2022/10/25 16:04:37 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rearrange_greater(struct token_stream **token_stream,
		struct token_stream *next, struct token_stream *prev,
		struct token_stream *iter)
{
	struct token_stream	*tmp;

	if (prev == iter)
	{
		*token_stream = next->next;
		next->next = NULL;
		tmp = *token_stream;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = iter;
	}
	else
	{
		prev->next = next->next;
		next->next = NULL;
		tmp = *token_stream;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = iter;
	}
}

void	rearrange_smaller(struct token_stream **token_stream,
			struct token_stream *prev, struct token_stream *iter,
			struct token_stream *next)
{
	prev->next = next->next;
	next->next = *token_stream;
	*token_stream = iter;
}

void	token_stream_rearrange(struct token_stream **token_stream)
{
	struct token_stream	*iter;
	struct token_stream	*next;
	struct token_stream	*prev;

	iter = *token_stream;
	prev = iter;
	next = iter->next;
	while (iter)
	{
		if (iter->token_name[0] == '<')
		{
			rearrange_smaller(token_stream, prev, iter, next);
			return ;
		}
		else if (iter->token_name[0] == '>')
		{
			rearrange_greater(token_stream, next, prev, iter);
			return ;
		}
		prev = iter;
		iter = iter->next;
		if (iter)
			next = iter->next;
	}
}

bool	can_be_arranged(struct token_stream *token_stream)
{
	if (token_stream->token_name[0] == '<')
		return (false);
	while (token_stream)
	{
		if (token_stream->token_name[0] == '<')
			return (true);
		token_stream = token_stream->next;
	}
	return (false);
}

bool	can_be_arranged_left(struct token_stream *token_stream)
{
	while (token_stream)
	{
		if (token_stream->token_name[0] == '>'
			&& token_stream->next
			&& token_stream->next->next
			&& token_stream->next->next->token_type > 7)
			return (true);
		token_stream = token_stream->next;
	}
	return (false);
}
