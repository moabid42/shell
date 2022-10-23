/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:09:37 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 16:28:42 by moabid           ###   ########.fr       */
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

t_env *create_the_env(char **env)
{
	t_env	*head;
	t_env	*list;
	char **split;
	int i;
	
	i = 0;
	head = malloc(sizeof(t_env));
	list = head;
	while(env[i]!= NULL)
	{
		split = split_name_content(env[i]);
		list->name = split[0];
		list->content = split[1];
		if(env[i+1]!= NULL)
		{
			list->next = new_node();
			list = list->next;
		}
		else
			list->next = NULL;
		i++;
	}
	return (head);
}


t_env	*minishell_env_init(char **env)
{
	t_env	*enviroment;

	enviroment = create_the_env(env);
	return (enviroment);
}
