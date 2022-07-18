/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhle <changhle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:12:37 by changhle          #+#    #+#             */
/*   Updated: 2022/03/04 22:12:37 by changhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_diu_sign(t_flag *flag, long nbr)
{
	int	ret;

	ret = 0;
	if (flag->f_plus > -1 && nbr >= 0)
	{
		write(1, "+", 1);
		ret++;
	}
	else if (!(flag->f_plus > -1) && flag->f_space > -1 && nbr >= 0)
	{
		write(1, " ", 1);
		ret++;
	}
	else if (nbr < 0)
	{
		write(1, "-", 1);
		ret++;
	}
	return (ret);
}

int	print_diu_nbr(t_flag *flag, long nbr)
{
	int	nbr_len;

	nbr_len = ft_nbr_len(nbr);
	if (nbr < 0)
		nbr_len--;
	while (flag->precision > nbr_len)
	{
		write(1, "0", 1);
		nbr_len++;
	}
	if (flag->dot == 1 && flag->precision == 0 && nbr == 0)
		return (0);
	ft_putnbr(nbr);
	return (nbr_len);
}

int	print_diu_zero(t_flag *flag, long nbr)
{
	int	nbr_len;
	int	ret;

	ret = 0;
	nbr_len = ft_nbr_len(nbr);
	if (flag->precision >= nbr_len)
	{
		nbr_len = flag->precision;
		if (nbr < 0)
			nbr_len++;
	}
	if (flag->dot == 1 && flag->precision == 0 && nbr == 0)
		nbr_len = 0;
	if (!(flag->f_minus > -1 || flag->dot == 1) && flag->f_zero > -1)
	{
		while (flag->width > nbr_len + ret)
		{
			write(1, "0", 1);
			ret++;
		}
	}
	return (ret);
}

int	print_diu_space(t_flag *flag, long nbr)
{
	int	nbr_len;
	int	ret;

	ret = 0;
	nbr_len = ft_nbr_len(nbr);
	if (flag->precision >= nbr_len)
	{
		nbr_len = flag->precision;
		if (nbr < 0)
			nbr_len++;
	}
	if (flag->dot == 1 && flag->precision == 0 && nbr == 0)
		nbr_len = 0;
	if ((flag->f_minus > -1 || flag->dot == 1) || !(flag->f_zero > -1))
	{
		while (flag->width > nbr_len + ret)
		{
			write(1, " ", 1);
			ret++;
		}
	}
	return (ret);
}

int	type_diu(t_flag *flag, va_list ap)
{
	int		ret;
	long	nbr;
	int		nbr_len;

	ret = 0;
	if (flag->type == 'u')
		nbr = va_arg(ap, unsigned int);
	else
		nbr = va_arg(ap, int);
	nbr_len = ft_nbr_len(nbr);
	if (flag->f_minus > -1)
	{
		ret += print_diu_sign(flag, nbr);
		ret += print_diu_nbr(flag, nbr);
		ret += print_diu_space(flag, nbr);
	}
	else
	{
		ret += print_diu_space(flag, nbr);
		ret += print_diu_sign(flag, nbr);
		ret += print_diu_zero(flag, nbr);
		ret += print_diu_nbr(flag, nbr);
	}
	return (ret);
}
