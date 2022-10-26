/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_create_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:15:57 by frame             #+#    #+#             */
/*   Updated: 2022/10/26 10:19:37 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

enum e_token_type	find_redirection(char *token)
{
	if (!my_strcmp(token, ">"))
		return (GREATER);
	else if (!my_strcmp(token, "<"))
		return (LESS);
	else if (!my_strcmp(token, ">>"))
		return (DOUBLE_GREATER);
	else
		return (DOUBLE_SMALLER);
}

enum e_token_type	find_var_shit(char *token, struct s_minishell *minishell)
{
	if (token[0] == '$'
		&& (token[1] == '\0'
			|| token[1] == '\"'
			|| token[1] == '\''
			|| minishell->single == true))
		return (WORD);
	else if (token[0] == '$')
		return (VARIABLE);
	else
		return (EQUAL);
}

enum e_token_type	find_logicalop(char *token)
{
	if (!my_strcmp(token, "&&"))
		return (AND);
	else
		return (OR);
}

enum e_token_type	find_bool(char *token)
{
	if (!my_strcmp(token, "true"))
		return (TRUE);
	else
		return (FALSE);
}

enum e_token_type	find_type(char *token, struct s_minishell *minishell)
{
	if (!my_strcmp(token, "|"))
		return (PIPE);
	else if (!my_strcmp(token, ">") || !my_strcmp(token, "<")
		|| !my_strcmp(token, ">>") || !my_strcmp(token, "<<"))
		return (find_redirection(token));
	else if (!my_strcmp(token, "&&") || !my_strcmp(token, "||"))
		return (find_logicalop(token));
	else if (token[0] == '$' || ft_strchr(token, '='))
		return (find_var_shit(token, minishell));
	else if (!my_strcmp(token, "*"))
		return (STAR);
	else if (!my_strcmp(token, "false") || !my_strcmp(token, "true"))
		return (find_bool(token));
	return (WORD);
}
