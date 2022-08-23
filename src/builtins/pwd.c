/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:47:09 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/20 12:14:15 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char *get_pwd()
{
	char	buf[256];
	char	*pwd;

	pwd = getcwd(buf, sizeof(buf));
	if(pwd == NULL)
		return (NULL);
	return (pwd);
}

int ft_pwd ()
{
	char	buf[256];
	char	*pwd;

	pwd = getcwd(buf, sizeof(buf));
	if(pwd == NULL)
		return (0);
	while(pwd++)
		write(1,pwd,1);
	return (0);
}