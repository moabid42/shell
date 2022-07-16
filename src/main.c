/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:00:05 by moabid            #+#    #+#             */
/*   Updated: 2022/07/12 21:09:16 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    struct minishell minishell;

    if (argc != 2 && my_strcmp(argv[0], NAME))
        ft_error(SYNTAX_ERROR);
    minishell_create(&minishell, env);
	minishell_run(&minishell);
	minishell_destroy(&minishell);
    return (0);
}