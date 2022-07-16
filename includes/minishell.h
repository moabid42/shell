/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:00:09 by moabid            #+#    #+#             */
/*   Updated: 2022/07/14 00:10:18 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "utils.h"
#include "input.h"
#include "get_next_line.h"

struct minishell {
	char	**env;
	char	**g_env;
	char	*prompt; // can be changed when exporting PS1
	char	*input_str;
	bool	variable;
	char	**variables;
};

#endif