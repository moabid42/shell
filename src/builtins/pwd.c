/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:47:09 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/27 21:52:52 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char *get_pwd()
{
	char	*buf;
	char	*pwd;

	buf = malloc(sizeof(char) * 256);
	pwd = getcwd(buf, 256);
	if(pwd == NULL)
		return (NULL);
	return (pwd);
}

int	ft_pwd (struct minishell *minishell)
{
	char	*pwd;
	int i;

	write(1, "DOOM\n", 5);
	pwd = get_pwd ();
	if(pwd == NULL)
		return (0);
	i = 0;
	while(pwd[i])
	{
		write(1, &pwd[i], 1);
		i++;
	}
	newline();
	free(pwd);
	return (0);
}
