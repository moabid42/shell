/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:09:37 by moabid            #+#    #+#             */
/*   Updated: 2022/08/28 19:13:01 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

//char	**minishell_env_init(struct minishell *minishell, char **env)
t_env	*minishell_env_init(char **env)
{
	t_env	*enviroment;

	enviroment = create_the_env(env);
	while(enviroment != NULL)
 	{
 		printf("%s = %s\n", enviroment->name, enviroment->content);
 		enviroment = enviroment->next;
 	}
	
	return (enviroment);
}

// void	minishell_env_destroy(struct minishell *minishell)
// {
	
// }