/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: changhle <changhle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:12:20 by changhle          #+#    #+#             */
/*   Updated: 2022/03/04 22:12:20 by changhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include "../libft.h"

typedef struct s_flag
{
	int	f_minus;
	int	f_plus;
	int	f_zero;
	int	f_hash;
	int	f_space;
	int	width;
	int	dot;
	int	precision;
	int	type;
}	t_flag;

int		ft_nbr_len(long nbr);
void	ft_putnbr(long n);
int		ft_xnbr_len(unsigned long long xnbr);
void	ft_putxnbr(t_flag *flag, unsigned long long xnbr);
int		ft_printf(const char *format, ...);
int		type_c(t_flag *flag, va_list ap);
int		type_s(t_flag *flag, va_list ap);
int		type_diu(t_flag *flag, va_list ap);
int		type_px_upx(t_flag *flag, va_list ap);
int		type_percent(t_flag *flag);

#endif
