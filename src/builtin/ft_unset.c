/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:21:03 by frmessin          #+#    #+#             */
/*   Updated: 2022/09/19 19:03:45 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

static t_env    *remove_env_var(t_env *enviroment, t_env *node_to_erase)
{
    t_env *tmp;

    tmp = enviroment;    
    if(tmp && tmp == node_to_erase)
    {
        tmp = tmp->next;
        free(node_to_erase);
    }
    else
    {
        while(tmp && tmp->next && tmp->next != node_to_erase)
            tmp = tmp->next;
    }
    if(tmp->next == node_to_erase)
    {
        tmp->next = (tmp->next)->next;
        free(node_to_erase);
    }
    return (enviroment);
}

void ft_unset(char **argv, struct minishell *minishell)
{
    t_env *tmp;
    int i;

    i = 0;
    tmp = minishell->env;
    if(!argv[1])
        write(1, "not enough arguments \n", 22);
    else
    {
        while(argv[i])
        {
            tmp = minishell->env;
            while(tmp)
            {
                if(!my_strcmp(argv[1],tmp->name))
                    {
                        printf("found %s", tmp->name);
                        minishell->env = remove_env_var(minishell->env, tmp);
                    }
                tmp = tmp->next;
            }
        }
    }
}
