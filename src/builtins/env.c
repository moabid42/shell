/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:18:18 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/20 12:14:01 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_env(int argc, char **argv, char **env)
{
	t_env	*enviroment;
	
  	enviroment = create_the_env(env);
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