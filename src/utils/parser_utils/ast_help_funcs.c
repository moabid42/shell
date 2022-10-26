/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_help_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:28:54 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:20:14 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    is_bracket(struct s_minishell *minishell, char *str)
{
    if (my_strcmp(str, "(") == 0 || my_strcmp(str, ")") == 0)
    {
        if (my_strcmp(str, "(") == 0)
            minishell->open++;
        else
            minishell->open--;
        return (true);
    }
    return (false);
}