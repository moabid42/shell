/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:31:52 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/26 17:38:47 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// bool ft_isdigit(char c)
// {
// 	if( '0'<= c && c <= '9')
// 		return (true);
// 	return (false);
// }

void ft_putstr(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}


void newline()
{
	write(1, "\n", 1);
}
