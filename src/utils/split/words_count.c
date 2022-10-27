/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:49:57 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/28 00:58:53 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

int	increase_i(char *string, char split_char, char *special)
{
	int		special_index;
	int		i;

	i = 0;
	(void)split_char;
	special_index = in_special(string[i], special);
	i += ignore_inside_special(&string[i], special[special_index]) + 1;
	return (i);
}

struct s_count {
	int		i;
	int		word_count;
	int		flag;
	int		len;
	char	split_char;
};

void	count_advance(struct s_count *count, char *string, char *special)
{
	if (in_special(string[count->i], special) >= 0 && count->flag == 0)
	{
		count->i += increase_i(&string[count->i], count->split_char, special);
		count->word_count++;
		count->flag = 1;
	}
	else if (in_special(string[count->i], special) >= 0 && count->flag == 1)
		count->i += increase_i(&string[count->i], count->split_char, special);
	else if (string[count->i] != count->split_char && count->flag == 0)
	{
		count->word_count++;
		count->flag = 1;
		count->i++;
	}
	else if (string[count->i] == count->split_char)
	{
		while (string[count->i] == count->split_char)
			count->i++;
		count->flag = 0;
	}
	else if (count->flag == 1)
		count->i++;
}

int	words_count(char *string, char split_char, char *special)
{
	struct s_count	count;

	count.i = 0;
	count.word_count = 0;
	count.flag = 0;
	count.len = ft_strlen(string);
	count.split_char = split_char;
	while (count.i < count.len)
		count_advance(&count, string, special);
	return (count.word_count);
}
