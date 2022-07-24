/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_strings_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:45:28 by moabid            #+#    #+#             */
/*   Updated: 2022/07/23 22:14:14 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser.h"
#include "utils.h"

bool	quotes_string_check(char **scripts_line)
{
	int count;

	count = 0;
	while (scripts_line)
	{
		if (count == 2)
			return (true);
		if (ft_strchr(*scripts_line, '\"'))
			count++;
		*scripts_line++;
	}
	return (false);
}



char	**new_split(char )