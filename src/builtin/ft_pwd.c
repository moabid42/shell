/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:47:09 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/26 13:24:24 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

char	*get_pwd(void)
{
	char	*buf;
	char	*pwd;

	buf = malloc(sizeof(char) * 256);
	pwd = getcwd(buf, 256);
	if (pwd == NULL)
		return (NULL);
	return (pwd);
}

void	ft_pwd(struct s_minishell *minishell)
{
	char	*pwd;
	int		i;

	pwd = get_pwd ();
	if (pwd == NULL)
		exit (0);
	i = 0;
	while (pwd[i])
	{
		write(1, &pwd[i], 1);
		i++;
	}
	newline();
	free(pwd);
	exit (0);
}
