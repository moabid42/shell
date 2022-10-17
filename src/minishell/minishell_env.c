/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:09:37 by moabid            #+#    #+#             */
/*   Updated: 2022/10/16 15:59:06 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

void print_the_env(t_env *enviroment)
{
	while(enviroment != NULL)
 	{
 		printf("%s = %s\n", enviroment->name, enviroment->content);
 		enviroment = enviroment->next;
 	}
}

t_env	*minishell_env_init(char **env)
{
	t_env	*enviroment;

	enviroment = create_the_env(env);
	return (enviroment);
}