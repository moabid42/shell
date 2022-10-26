/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_crossing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:23:58 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 02:33:31 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin_ast(char *cmd)
{
	return (!my_strcmp(cmd, "export")
		|| !my_strcmp(cmd, "cd")
		|| !my_strcmp(cmd, "exit")
		|| !my_strcmp(cmd, "unset"));
}

bool	ast_is_simple(struct ast *ast)
{
	if (ast->value.token_type == COMMAND
		|| ast->value.token_type == DOUBLE_SMALLER
		|| ast->value.token_type == LESS
		|| (ast->value.token_type == GREATER
			&& ast->left->value.token_type != PIPE)
		|| (ast->value.token_type == DOUBLE_GREATER
			&& ast->left->value.token_type != PIPE)
		|| is_builtin(ast->value.token_name) == true)
		return (true);
	return (false);
}

int	openfile(char *file, int re_or_wr)
{
	int	ret;

	if (re_or_wr == 0)
	{
		ret = open(file, O_RDONLY, 0777);
		if (access(file, F_OK | R_OK) != 0)
		{
			dprintf(2, "esh: no such file or directory: %s\n", file);
			return (-1);
		}
	}
	if (re_or_wr == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (re_or_wr == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}
