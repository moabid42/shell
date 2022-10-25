/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:31:52 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/26 01:49:50 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

/*
bool ft_isdigit(char c)
{
	if( '0'<= c && c <= '9')
		return (true);
	return (false);
}
*/

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	newline(void)
{
	write(1, "\n", 1);
}
