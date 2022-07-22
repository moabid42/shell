/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhle <changhle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:12:51 by changhle          #+#    #+#             */
/*   Updated: 2022/03/04 22:12:51 by changhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(t_flag *flag, char *str)
{
	int	str_len;
	int	ret;

	ret = 0;
	str_len = ft_strlen(str);
	if (flag->precision < str_len && flag->dot == 1)
		str_len = flag->precision;
	while (str_len > ret)
	{
		write(1, (str++), 1);
		ret++;
	}
	return (ret);
}

int	print_s_space(t_flag *flag, char *str)
{
	int	str_len;
	int	ret;

	ret = 0;
	str_len = ft_strlen(str);
	if (flag->precision < str_len && flag->dot == 1)
		str_len = flag->precision;
	while (flag->width - str_len > ret)
	{
		if (!(flag->f_minus > -1) && flag->f_zero > 0)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		ret++;
	}
	return (ret);
}

int	type_s(t_flag *flag, va_list ap)
{
	int		ret;
	char	*str;

	ret = 0;
	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	if (flag->f_minus > -1)
	{
		ret += print_str(flag, str);
		ret += print_s_space(flag, str);
	}
	else
	{
		ret += print_s_space(flag, str);
		ret += print_str(flag, str);
	}
	return (ret);
}
