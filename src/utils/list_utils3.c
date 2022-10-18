/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:20:52 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 13:15:05 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/utils.h"

enum e_token_type	find_pipe_or_space(char *token)
{
	if (!my_strcmp(token, "|"))
		return (PIPE);
	else
		return (BACKSLASH);
}

enum e_token_type	find_var_shit(char *token)
{
	if (token[0] == '$')
		return (VARIABLE);
	else
		return (EQUAL);
}

enum e_token_type	find_logicalop(char *token)
{
	if (!my_strcmp(token, "&&"))
		return (ANDAND);
	else
		return (OROR);
}

enum e_token_type	find_bool(char *token)
{
	if (!my_strcmp(token, "true"))
		return (TRUE);
	else
		return (FALSE);
}

enum e_token_type	find_type(char *tk)
{
	if (!my_strcmp(tk, " ") || !my_strcmp(tk, "\t")
		|| !my_strcmp(tk, "\v") || !my_strcmp(tk, "\f")
		|| !my_strcmp(tk, "\r") || !my_strcmp(tk, "\n")
		|| !my_strcmp(tk, "|") || !my_strcmp(tk, "\\"))
		return (find_pipe_or_space(tk));
	else if (!my_strcmp(tk, ">") || !my_strcmp(tk, "<")
		|| !my_strcmp(tk, ">>") || !my_strcmp(tk, "<<"))
		return (find_redirection(tk));
	else if (!my_strcmp(tk, "&&") || !my_strcmp(tk, "||"))
		return (find_logicalop(tk));
	else if (tk[0] == '\"' || tk[0] == '\'')
		return (find_quotes(tk));
	else if (!my_strcmp(tk, "\\"))
		return (BACKSLASH);
	else if (tk[0] == '$' || ft_strchr(tk, '='))
		return (find_var_shit(tk));
	else if (!my_strcmp(tk, "*") || !my_strcmp(tk, "!")
		|| !my_strcmp(tk, "?"))
		return (find_wildcard(tk));
	else if (!my_strcmp(tk, "(") || !my_strcmp(tk, ")") || !my_strcmp(tk, "[")
		|| !my_strcmp(tk, "]") || !my_strcmp(tk, "{") || !my_strcmp(tk, "}"))
		return (find_parenth(tk));
	else if (!my_strcmp(tk, "false") || !my_strcmp(tk, "true"))
		return (find_bool(tk));
	return (WORD);
}
