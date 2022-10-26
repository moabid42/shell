/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:06:40 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:33:01 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	export(struct s_minishell *minishell, struct s_token_stream *prev)
{
	if (!my_strcmp(prev->token_name, "export"))
		minishell->export_fg = true;
	return (false);
}

bool	a_right(struct s_ast *ast, struct s_minishell *minishell)
{
	if (ast->value.token_type == LESS)
		minishell->start_right = true;
	return (false);
}

void	advance(struct s_token_stream **prev, struct s_token_stream **tmp)
{
	*prev = *tmp;
	*tmp = (*tmp)->next;
}

struct s_ast	*check_bracket_and_assign(struct s_minishell *minishell,
		struct s_token_stream **stm)
{
	if (is_bracket(minishell, (*stm)->token_name) == true)
		(*stm) = (*stm)->next;
	return (ast_create_first_node(minishell, *stm));
}
