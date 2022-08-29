/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:09:37 by moabid            #+#    #+#             */
/*   Updated: 2022/08/29 16:49:32 by moabid           ###   ########.fr       */
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
//char	**minishell_env_init(struct minishell *minishell, char **env)
t_env	*minishell_env_init(char **env)
{
	t_env	*enviroment;

	enviroment = create_the_env(env);
	//print_the_env(enviroment);
	char **j = env_to_string(enviroment);
	j = NULL;
	return (enviroment);
}

// void	minishell_env_destroy(struct minishell *minishell)
// {
	
// }