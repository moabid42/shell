/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statement_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:29:51 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 02:38:44 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	less_statement_execute(char **command_statement,
			struct ast *ast, struct minishell *minishell, int fd_out)
{
	pid_t	pid;
	int		fd_in;

	fd_in = openfile(command_statement[1], 0);
	if (fd_in == -1)
		rise_error_and_exit(ast);
	if (ast->right == NULL)
		;
	else
	{
		pid = fork();
		if (pid == -1)
			ft_error("FORK ERROR");
		if (!pid)
		{
			dup2(fd_out, 1);
			dup2(fd_in, 0);
			command_statement_execute_complexe(ast->right, minishell);
		}
		else
			wait(NULL);
	}
	close(fd_in);
}

int	get_fd_out(struct ast *ast, struct ast **jump)
{
	int	fd_out;

	if (ast->value.token_type == GREATER)
	{
		if (ast->right == NULL)
			return (-1);
		fd_out = openfile(ast->right->value.token_name, 1);
		(*jump) = (*jump)->left;
	}
	else if (ast->value.token_type == DOUBLE_GREATER)
	{
		fd_out = openfile(ast->right->value.token_name, 2);
		(*jump) = (*jump)->left;
	}
	else
		fd_out = 1;
	return (fd_out);
}
