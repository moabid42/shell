/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:21:03 by frmessin          #+#    #+#             */
/*   Updated: 2022/09/08 10:23:12 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
    
    printf("i'm here");
    tmp = minishell->env;
    if(!argv[1])
        write(1, "not enough arguments \n", 22);
    else
        while(tmp)
        {
            if(!my_strcmp(argv[1],tmp->name))
                {
                    printf("found %s", tmp->name);
                    minishell->env = remove_env_var(minishell->env, tmp);
                    exit (1);
                }
            tmp = tmp->next;
        }
    exit (0);
}
