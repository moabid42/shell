/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:18:35 by moabid            #+#    #+#             */
/*   Updated: 2022/10/25 17:18:36 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	var_handle(struct minishell *minishell,
	struct token_stream *token_stream, struct ast *tmp)
{
	tmp->value.token_name = minishell_find_variable(minishell,
			token_stream->token_name);
	tmp->value.token_type = WORD;
	if (tmp->value.token_name == NULL)
		tmp->value.token_name = ft_strdup("");
}

static void	cmd_handle(struct minishell *minishell,
	struct token_stream *token_stream,
	struct ast *tmp)
{
	if (ft_iscommand(tmp->value.token_name, minishell->env) == true
		|| ft_isexecutable(tmp->value.token_name) == true)
		tmp->value.token_type = COMMAND;
	else if (is_builtin(tmp->value.token_name) == true
		|| !my_strcmp(tmp->value.token_name, "exit"))
		tmp->value.token_type = BUILTIN;
}

struct ast	*ast_create_first_node(struct minishell *minishell,
			struct token_stream *token_stream)
{
	struct ast	*tmp;

	tmp = ft_malloc(sizeof(struct ast));
	if (token_stream->token_type == VARIABLE)
		var_handle(minishell, token_stream, tmp);
	else
	{
		tmp->value.token_name = token_stream->token_name;
		tmp->value.token_type = token_stream->token_type;
	}
	if (tmp->value.token_type == WORD || tmp->value.token_type == VARIABLE)
		cmd_handle(minishell, token_stream, tmp);
	tmp->isroot = true;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}
