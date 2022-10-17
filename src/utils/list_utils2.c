/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:20:46 by moabid            #+#    #+#             */
/*   Updated: 2022/10/17 14:10:16 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/utils.h"

struct s_scripts	*ft_create_stack_scripts(char **scripts_line, unsigned int count) {
	int i;
	struct s_scripts *new_node;
	struct s_scripts *curr;

	i = 0;
	new_node = (struct s_scripts *) ft_malloc(sizeof(struct s_scripts));
	curr = new_node;
	while (i < count) {
		if (i < count - 1)
			new_node->next = (struct s_scripts *) ft_malloc(sizeof(struct s_scripts));
		new_node->input_line = ft_strdup(scripts_line[i]);
		new_node->have_herdoc = 0;
		if (i == (count - 1))
			new_node->next = NULL;
		else
			new_node = new_node->next;
		i++;
	}
	return (curr);
}

enum e_token_type	find_parenth(char *token) {
	if (!my_strcmp(token, "("))
		return (PARENTHS_OP);
	else if (!my_strcmp(token, ")"))
		return (PARENTHS_CL);
	else if (!my_strcmp(token, "["))
		return (SQUARE_BRACKETS_OP);
	else if (!my_strcmp(token, "]"))
		return (SQUARE_BRACKETS_CL);
	else if (!my_strcmp(token, "{"))
		return (CURLY_BRACKERTS_OP);
	else
		return (CURLY_BRACKERTS_CL);
}

enum e_token_type	find_quotes(char *token) {
	if (token[0] == '\"')
		return (STRING_DOUBLE);
	else
		return (STRING_SINGLE);
}

enum e_token_type	find_wildcard(char *token) {
	if (!my_strcmp(token, "*"))
		return (STAR);
	else if (!my_strcmp(token, "!"))
		return (EXCAMATION);
	else
		return (QUESTION);
}

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
