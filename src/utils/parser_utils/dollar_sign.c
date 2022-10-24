/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:13:29 by frame             #+#    #+#             */
/*   Updated: 2022/10/24 11:15:56 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_alphanumeric(char c)
{
	if (('0' <= c && c <= '9') || \
		('a' <= c && c <= 'z') || \
		('A' <= c && c <= 'Z'))
		return (true);
	return (false);
}

struct s_data
{
	int		i;
	int		j;
	bool	open;
	char	q_type;
	char	*ret_str;
	char	*str;
};

static void	parentesis_open(struct s_data *d)
{
	d->open = true;
	d->q_type = d->str[d->i];
	d->ret_str[d->j++] = d->str[d->i++];
}

static void	open_true_dollarsign(struct s_data *d)
{
	d->ret_str[d->j++] = d->q_type;
	d->ret_str[d->j++] = ' ';
	if (d->str[d->i + 1])
		d->ret_str[d->j++] = d->str[d->i++];
	while (d->str[d->i] && is_alphanumeric(d->str[d->i]) == true
		&& d->str[d->i] != '$')
	{
		d->ret_str[d->j] = d->str[d->i];
		d->i++;
		d->j++;
	}
	d->ret_str[d->j++] = ' ';
	d->ret_str[d->j++] = d->q_type;
}

static void	closed_true_dollarsign(struct s_data *d)
{
	d->ret_str[d->j++] = ' ';
	if (d->str[d->i + 1])
		d->ret_str[d->j++] = d->str[d->i++];
	while (d->str[d->i] && is_alphanumeric(d->str[d->i]) == true
		&& d->str[d->i] != '$')
	{
		d->ret_str[d->j] = d->str[d->i];
		d->i++;
		d->j++;
	}
	d->ret_str[d->j++] = ' ';
}

static void	data_init(char *str, struct s_data *d)
{
	d->i = 0;
	d->j = 0;
	d->open = false;
	d->ret_str = malloc(100000);
	d->ret_str[100000 - 1] = '\0';
	d->str = str;
}

static void	closed_quotes(struct s_data *d)
{
	d->open = false;
	d->ret_str[d->j] = d->str[d->i];
	d->i++;
	d->j++;
}

static void	other_cases(struct s_data *d)
{
	d->ret_str[d->j] = d->str[d->i];
	d->i++;
	d->j++;
}

char	*string_dollar_sign(char *str)
{
	struct s_data	d;

	data_init(str, &d);
	while (d.str[d.i])
	{
		if ((d.str[d.i] == '\'' || d.str[d.i] == '\"') && d.open == false)
			parentesis_open(&d);
		else if (d.open == true && d.str[d.i] == '$')
			open_true_dollarsign(&d);
		else if (d.open == false && d.str[d.i] == '$')
			closed_true_dollarsign(&d);
		else if (d.str[d.i] == d.q_type && d.open == true)
			closed_quotes(&d);
		else if (d.str[d.i])
			other_cases(&d);
	}
	d.ret_str[d.j] = '\0';
	return (d.ret_str);
}
