/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 22:52:20 by frmessin          #+#    #+#             */
/*   Updated: 2022/07/24 20:14:56 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parser.h"
#include "utils.h"

static bool	char_exist(char *str, char c)
{
	int i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool	quotes_string_check(char **scripts_line, int num)
{
	int count;
	int	i;

	count = 0;
	i = 0; 
	while (i < num)
	{
		if (char_exist(scripts_line[i], '\"') || char_exist(scripts_line[i], '\''))
			count++;
		i++;
	}
	if (count == 2)
		return (true);
	return (false);
}

char	*manage_word(int *start, char *string, char *special, char split_char)
{
	int		i;
	int		special_index;
	char	*word;
	
	i = *start;
	while(string[i] != split_char && string[i] != '\0')
	{
		if(in_special(string[i], special) >= 0)
		{
			special_index = in_special(string[i], special);
			i += ignore_inside_special(&string[i], special[special_index]);
			if(string[i] != '\0')
				i++;
		}
		else
			i++;  
	}
	// printf(" start :%d i:%d i - start: %d\n", *start,i,i - *start);
	// fflush(NULL);
	word = ft_cutter (&string[*start], i - *start);
	*start = i;
	return (word);
}

char	**ft_new_split(char *string, char split_char, char* special)
{
	int		i;
	int		tab;
	char	**split_string;

	split_string = malloc(sizeof(char*) * words_count(string, split_char, special) + 1);
		if(split_string == NULL)
			return NULL;
	tab = 0;
	i = 0;
	while(i < ft_strlen(string))
	{
		if(string[i] != split_char)
		{
			split_string[tab] = manage_word(&i, string, special, split_char);
			// printf("%s \n", split_string[tab]);
			//printf("index : %d %s tab \n", split_string[tab]);
			tab++;
		}
		i++;
	}	
	split_string[tab] = NULL;
	return (split_string);
}

// int main ()
// {
// 	char		**j;//       [c][1][2][3][;]
// 	j = ft_new_split("adavo a centa ;ll\"ora ;per\" veder;e la partita", ';', "\"'");
// 	return 0;
// }