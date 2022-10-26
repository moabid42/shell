/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:53:19 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 09:37:45 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isexecutable(char *executable)
{
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	if (stat(executable, buf) == 0)
	{
		if (buf->st_mode & S_IXUSR)
		{
			free(buf);
			return (true);
		}
	}
	free(buf);
	return (false);
}

struct s_ast	*find_end_right(struct s_ast *node)
{
	if (!node->right)
		return (node);
	node = node->right;
	while (node->left)
		node = node->left;
	return (node);
}

struct s_ast	*handle_not_right_2(struct s_minishell *minishell,
		struct s_ast *ast)
{
	minishell->return_value = 127;
	if (!ast->left)
		dprintf(2, "esh: %s: command not found ..\n", ast->value.token_name);
	else
		dprintf(2, "esh: %s: command not found ..\n",
			ast->left->value.token_name);
	return (NULL);
}

bool	is_sub_tree(int export_fg, struct s_token_stream *prev,
			struct s_token_stream *tmp)
{
	return (export_fg == false
		&& prev->token_type == EQUAL
		&& tmp->token_type != AND
		&& tmp->token_type != OR
		&& tmp->token_type != EQUAL);
}

struct s_ast	*handle_not_right(struct s_minishell *minishell,
		struct s_ast *ast)
{
	minishell->return_value = 127;
	if (!ft_isalnum(ast->value.token_name[0]))
		;
	else if (ast->left)
		dprintf(2, "esh: %s: command not found ...\n",
			ast->left->value.token_name);
	else
		dprintf(2, "esh: %s: command not found ...\n",
			ast->value.token_name);
	minishell->handled = true;
	return (NULL);
}
