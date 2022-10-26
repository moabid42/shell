/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:33:37 by frame             #+#    #+#             */
/*   Updated: 2022/10/26 09:37:58 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parentesis_open(struct s_data *d)
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
