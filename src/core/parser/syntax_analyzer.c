/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:33:39 by moabid            #+#    #+#             */
/*   Updated: 2022/10/27 14:41:09 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

struct s_scripts	*ft_create_node_script(char *cmd)
{
	struct s_scripts	*new_node;

	new_node = malloc(sizeof(struct s_scripts));
	new_node->input_line = ft_strdup(cmd);
	new_node->next = NULL;
	return (new_node);
}

bool	check_for_pipes(struct s_token_stream *tmp)
{
	while (tmp)
	{
		if (tmp->token_name[0] == '|')
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

bool	syntax_analyzer_create(struct s_token_stream *token_stream,
		struct s_ast *ast, struct s_minishell *minishell)
{
	struct s_ast			*tmp;
	struct s_token_stream	*iterator;

	tmp = ast;
	iterator = token_stream;
	if (iterator->token_type < 3)
	{
		minishell->return_value = 258;
		dprintf(2, "esh: syntax error near unexpected token \
				`%s'\n", iterator->token_name);
		return (false);
	}
	if (ast->value.token_type < 5 && ast->right == NULL
		&& minishell->handled == false)
	{
		minishell->return_value = 258;
		dprintf(2, "esh: syntax error near unexpected token \
				`%s'\n", tmp->value.token_name);
		return (false);
	}
	return (true);
}
