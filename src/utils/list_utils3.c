/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:20:52 by moabid            #+#    #+#             */
/*   Updated: 2022/10/17 14:09:13 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/utils.h"

enum e_token_type find_pipe_or_space(char *token)
{
	if (!my_strcmp(token, "|"))
		return (PIPE);
	else
		return (BACKSLASH);
}

enum e_token_type find_var_shit(char *token) {
	if (token[0] == '$')
		return (VARIABLE);
	else
		return (EQUAL);
}

enum e_token_type find_logicalop(char *token) {
	if (!my_strcmp(token, "&&"))
		return (ANDAND);
	else
		return (OROR);
}

enum e_token_type find_bool(char *token) {
	if (!my_strcmp(token, "true"))
		return (TRUE);
	else
		return (FALSE);
}

enum e_token_type find_type(char *token)
{
	if (!my_strcmp(token, " ") || !my_strcmp(token, "\t")
	    || !my_strcmp(token, "\v") || !my_strcmp(token, "\f")
	    || !my_strcmp(token, "\r") || !my_strcmp(token, "\n")
	    || !my_strcmp(token, "|") || !my_strcmp(token, "\\"))
		return (find_pipe_or_space(token));
	else if (!my_strcmp(token, ">") || !my_strcmp(token, "<")
		   || !my_strcmp(token, ">>") || !my_strcmp(token, "<<"))
		return (find_redirection(token));
	else if (!my_strcmp(token, "&&") || !my_strcmp(token, "||"))
		return (find_logicalop(token));
	else if (token[0] == '\"' || token[0] == '\'')
		return (find_quotes(token));
	else if (!my_strcmp(token, "\\"))
		return (BACKSLASH);
	else if (token[0] == '$' || ft_strchr(token, '='))
		return (find_var_shit(token));
	else if (!my_strcmp(token, "*") || !my_strcmp(token, "!")
		   || !my_strcmp(token, "?"))
		return (find_wildcard(token));
	else if (!my_strcmp(token, "(") || !my_strcmp(token, ")")
		   || !my_strcmp(token, "[") || !my_strcmp(token, "]")
		   || !my_strcmp(token, "{") || !my_strcmp(token, "}"))
		return (find_parenth(token));
	else if (!my_strcmp(token, "false") || !my_strcmp(token, "true"))
		return (find_bool(token));
		return (WORD);
}
