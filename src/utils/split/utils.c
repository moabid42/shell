/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:40:01 by frmessin          #+#    #+#             */
/*   Updated: 2022/07/24 19:56:37 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

int		in_special( char c, char *special)
{
	int i;

	i = 0;
	while(special[i])
	{
		if(c == special[i])
			return (i);
		i++;
	}
	return (-1);
}

int		ignore_inside_special(char *string, char special)
{
	int i;

	i = 0;
	if(string[i] == special)
	{
		i++;
		while(string[i] != special)
		{
			i++;
			if(string[i] == '\0')
			{
				//should it return error?
				break;
			}
		}
	}
	return i;
}

char	*ft_cutter (char *string, int n_byte)
{
	char *copy;
	int i;

	i = 0;
	copy = malloc( n_byte + 1);
	if(copy == NULL)
		return NULL;
	while(i < n_byte)
	{
		copy[i] = string[i];
		i++;
	}
	copy[n_byte] = '\0';
	return (copy);
}
