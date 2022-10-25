/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:52:43 by frame             #+#    #+#             */
/*   Updated: 2022/10/26 01:55:21 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

unsigned long long	ft_atoi_big(const char *str)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (!my_strcmp(str, "9223372036854775808"))
		return (255);
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		num = num * 10 + *str++ - '0';
	if ((num * sign) == (MIN_SIZE - 1))
		return (-42);
	else if ((num * sign) == (MAX_SIZE + 1))
		return (42);
	if (((num * sign) >= MAX_SIZE || (num * sign) <= MIN_SIZE))
		return (0);
	return (num * sign);
}

int	ft_atoi_special(char *str)
{
	long long	num;

	num = ft_atoi_big(str);
	if (num < 0)
	{
		if (num == -42 && ft_strlen(str) > 3)
			return (0);
		return (num + 256);
	}
	else
	{
		if (num == 42 && ft_strlen(str) > 2)
			return (255);
		else if (num == 0 && ft_strlen(str) > 1)
			return (255);
		return (num % 256);
	}
}
