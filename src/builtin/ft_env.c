/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:18:18 by frmessin          #+#    #+#             */
/*   Updated: 2022/09/19 19:08:25 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"


void ft_env(t_env *enviroment)
{
 	while(enviroment != NULL)
 	{
		ft_putstr_fd(enviroment->name, 1);
		write(1, "=", 1);
		ft_putstr_fd(enviroment->content, 1);
		write(1, "\n", 1);
 		enviroment = enviroment->next;
 	}
	exit(0);
}
