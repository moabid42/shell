/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:49:57 by frmessin          #+#    #+#             */
/*   Updated: 2022/07/24 19:56:02 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parser.h"
#include "utils.h"


int increase_i(char *string, char split_char, char *special)
{
	int		special_index;
	int i;

	i = 0;
	special_index = in_special(string[i], special);
	i = ignore_inside_special(&string[i], special[special_index]) + 1;
	return i;
}

int		words_count(char *string, char split_char, char *special)
{
	int		i;
	int		flag;
	int		word_count;

	flag = 0;
	word_count = 0;
	i = 0;
	while(i < ft_strlen(string))
	{
		if(in_special(string[i], special) >= 0 && flag == 0)
		{
			i += increase_i(string, split_char, special);
			word_count++;
			flag = 1;
		}
		else if(in_special(string[i], special) >= 0 && flag == 1)
			i += increase_i(string, split_char, special);
		else if(string[i] != split_char && flag == 0)
		{
			word_count++;
			flag = 1;
			i++;
		}
		else if(string[i] == split_char)
		{
			while(string[i] == split_char)
				i++;
			flag = 0;
		}
		else if(flag == 1)
			i++;
	}
	return (word_count);
}
