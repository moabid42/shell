/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:19:44 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/26 01:42:43 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

bool	string_value_cmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		if (str1[i] < str2[i])
			return (true);
		if (str1[i] > str2[i])
			return (false);
	}
	return (true);
}

int	find_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	else
		return (-1);
}

bool	bool_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while ((str1[i] && str2[i]) && (str1[i] == str2[i]))
		i++;
	if (str1[i] != str2[i])
		return (false);
	return (true);
}

bool	check_string(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}
