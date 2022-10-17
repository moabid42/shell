/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:11:55 by moabid            #+#    #+#             */
/*   Updated: 2022/10/17 14:08:53 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"

bool	ft_isword(char *str)
{
	int i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void	minishell_error(struct s_minishell *minishell, char *str)
{
	minishell->return_value = 1;
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
