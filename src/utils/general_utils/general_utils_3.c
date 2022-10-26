/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:54:47 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 12:54:51 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

int	my_strcmp(const char *strg1, char *strg2)
{
	if ((strg1 == NULL && strg2 == NULL))
		return (0);
	else if (!strg1 || !strg2)
		return (1);
	while ((*strg1 != '\0' && *strg2 != '\0') && *strg1 == *strg2)
	{
		strg1++;
		strg2++;
	}
	if (*strg1 == *strg2)
		return (0);
	else
		return (*strg1 - *strg2);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr)
		ft_bzero(ptr, size);
	else
	{
		free(ptr);
		exit(1);
	}
	return (ptr);
}

unsigned int	ft_get_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	if (nb_strs == 0)
		return (1);
	return (nb_strs);
}

int	ft_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r' \
	|| c == '\t' || c == '\v' || c == ' ');
}
