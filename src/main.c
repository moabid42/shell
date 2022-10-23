/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:00:05 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 22:02:20 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

int	main(int argc, char **argv, char **env)
{
	struct minishell	minishell;
	int					exit_status;

	if (argc != 1)
		ft_error(SYNTAX_ERROR);
	else if (*env == NULL)
		exit(1);
	minishell_create(&minishell, env);
	minishell_run(&minishell);
	exit_status = minishell.return_value;
	minishell_destroy(&minishell);
	return (exit_status);
}
