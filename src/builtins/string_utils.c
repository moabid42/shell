/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:19:44 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/28 19:21:20 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool string_value_cmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while(str1[i] && str2[i])
	{
		if(str1[i] == str2[i])
			i++;
		if(str1[i] < str2[i])
			return (true);
		if(str1[i] > str2[i])
			return (false);
	}
	return (true);
}

int find_chr(char *str, char c)
{
	int i;

	i = 0;
	while(str[i] && str[i] != c)
		i++;
	if(str[i] == c)
		return (i);
	else
		return (-1);
}

bool bool_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while((str1[i] && str2[i]) && (str1[i] == str2[i]))
		i++;
	if(str1[i]!=str2[i])
		return (false);
	return (true);
}


bool check_string(char c, char *str)
{
	int i;
	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return(true);
		i++;
	}
	return (false);
}
