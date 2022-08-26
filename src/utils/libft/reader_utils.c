/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:22:52 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/26 18:39:45 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

// char	*ft_strchr(const char *s, int c)
// {
// 	int		i;
// 	char	char_c;

// 	i = 0;
// 	char_c = (char)c;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == char_c)
// 			return ((char *)s + i);
// 		i++;
// 	}
// 	if (c == '\0')
// 		return ((char *)s + i);
// 	return (0);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

int	check_for_word(char *string, t_args *args)
{
	int		i;
	int		n;
	bool	word;

	i = 0;
	n = 0;
	word = false;
	while (string[i])
	{
		if (ft_strchr(args->ign_char_inside, string[i]) != NULL)
			i += jump_char_inside(&string[i], args->ign_char_inside, &n, &word);
		else if (ft_strchr(args->ignore, string[i]) != NULL)
			i = found_char_to_ignore(&n, i, string, &word);
		else if (single_word_strchr(args->single_word, &string[i]) > 0)
			return (i);
		else if (ft_strchr(args->split_char, string[i]) != NULL)
		{
			found_split_char(i, &word);
			return (i);
		}
		else
			i = found_word(&word, i, &n);
		if (word == false)
			return (i);
	}
	return (i);
}

char	*create_the_word(char *string, int n)
{
	int		i;
	char	*new_string;

	i = 0;
	new_string = malloc((sizeof(char)) * n);
	if (new_string == NULL)
		return (NULL);
	new_string[n] = '\0';
	while (i < n)
	{
		new_string[i] = string[i];
		i++;
	}
	return (new_string);
}
