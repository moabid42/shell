/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:33:39 by moabid            #+#    #+#             */
/*   Updated: 2022/10/13 16:57:37 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

// void	token_stream_tokenize(struct token_stream *token_stream)
// {

// }

void iterator_check(struct token_stream *iterator, struct token_stream *tmp) {

}

bool iterator_create(struct token_stream **iterator, struct token_stream **tmp) {
	if (((*tmp)->token_type == STRING_DOUBLE
		|| (*tmp)->token_type ==  STRING_SINGLE
		|| (*tmp)->token_type == BACKSLASH
		|| (*tmp)->token_name[ft_strlen((*tmp)->token_name) - 1] == '\\'
	    || (*tmp)->token_type == PARENTHS_OP
	    || (*tmp)->token_type == SQUARE_BRACKETS_OP
	    || (*tmp)->token_type == CURLY_BRACKERTS_OP)
	    && (*tmp)->closed == false)
	{
		*iterator = *tmp;
		// printf("Iterator created for %d!!\n", (*iterator)->token_type);
		return (true);
	}
	else
		return (false);
}

bool iterator_check_backslash(struct token_stream **iterator)
{
	if ((((*iterator)->token_type == BACKSLASH && (*iterator)->next == NULL)
		|| ((*iterator)->token_name[ft_strlen((*iterator)->token_name) - 1] == '\\'))
		&& ft_strlen((*iterator)->token_name) > 1)
			return (true);
	return (false);
}

void iterator_trigger_heredoc(struct scripts **script) {
	// printf("We did trigger heredoc \n");
	(*script)->have_herdoc++;
}

bool iterator_pth_br_closure_met(struct token_stream **tmp) {
	if ((*tmp)->token_type == PARENTHS_CL
	    || (*tmp)->token_type == SQUARE_BRACKETS_CL
	    || (*tmp)->token_type == CURLY_BRACKERTS_CL)
		return (true);
	return (false);
}

bool iterator_check_pth_br(struct token_stream **iterator) {
	while (*iterator) {
		if (iterator_pth_br_closure_met(iterator) == true)
			return (true);
		*iterator = (*iterator)->next;
	}
	return (false);
}

bool	heredoc_rediraction(struct token_stream **iterator)
{
	if ((*iterator)->token_type == DOUBLE_GREATER)
		return (true);
	return (false);
}

void iterator_trigger_error(struct token_stream *tmp)
{

}

bool	check_string_closed(struct token_stream **token_stream)
{
	if ((*token_stream)->token_type == STRING_DOUBLE
		|| (*token_stream)->token_type == STRING_SINGLE)
	{
		if ((*token_stream)->token_name[0] 
			== (*token_stream)->token_name[ft_strlen((*token_stream)->token_name) - 1]
			&& ft_strlen((*token_stream)->token_name) != 1)
			return (true);
		// printf("We found a heredoc\n");
		return (false);
	}
	return (true);
}

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
