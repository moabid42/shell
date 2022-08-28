/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:18:18 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/28 19:06:41 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_env(t_env *env)
{
	t_env	*enviroment;
	
  	//enviroment = create_the_env(env);
 	while(enviroment != NULL)
 	{
 		printf("%s=%s\n", enviroment->name, enviroment->content);
 		enviroment = enviroment->next;
 	}
	return (0);
}

// int main (int argc, char **argv, char **env)
// {
// 	return (ft_env(argc, argv, env));
// }