/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhle <changhle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:12:59 by changhle          #+#    #+#             */
/*   Updated: 2022/03/05 23:03:23 by changhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbr_len(long nbr)
{
	int				len;
	unsigned int	u_nbr;

	if (nbr > 0)
		len = 0;
	else
	{
		nbr *= -1;
		len = 1;
	}
	u_nbr = (unsigned int)nbr;
	while (u_nbr > 0)
	{
		u_nbr /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr(long n)
{
	char	c;

	if (n < 0)
		n = n * -1;
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		c = '0' + n % 10;
		write(1, &c, 1);
	}
	else
	{
		c = '0' + n;
		write(1, &c, 1);
	}
}

int	ft_xnbr_len(unsigned long long xnbr)
{
	int	len;

	len = 1;
	while (xnbr > 15)
	{
		xnbr /= 16;
		len++;
	}
	return (len);
}

void	ft_putxnbr(t_flag *flag, unsigned long long xnbr)
{
	const char	*lower_x = "0123456789abcdef";
	const char	*upper_x = "0123456789ABCDEF";

	if (xnbr > 15)
		ft_putxnbr(flag, xnbr / 16);
	if (flag->type == 'x' || flag->type == 'p')
		write(1, &lower_x[xnbr % 16], 1);
	else if (flag->type == 'X')
		write(1, &upper_x[xnbr % 16], 1);
}
