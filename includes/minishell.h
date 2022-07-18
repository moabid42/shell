/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:00:09 by moabid            #+#    #+#             */
/*   Updated: 2022/07/17 01:25:40 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/utils/libft/libft.h"
#include "utils.h"
#include "parser.h"
#include "../src/utils/libft/get_next_line.h"

struct minishell {
	char	**env;
	char	**g_env;
	char	*prompt; // can be changed when exporting PS1
	char	*input_str;
	bool	variable;
	char	**variables;
	int		scripts_num;
	struct	scripts *scripts;
};

void    minishell_create(struct minishell *minishell, char **env);
char	*minishell_get_input();
void    minishell_destroy(struct minishell *minishell);
void    minishell_run(struct minishell *minishell);
void	minishell_process_input(struct minishell *minishell);
char	**minishell_env_init(char **env);

#endif