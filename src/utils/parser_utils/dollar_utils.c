/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:04:03 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 13:04:07 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closed_quotes(struct s_data *d)
{
	d->open = false;
	d->ret_str[d->j] = d->str[d->i];
	d->i++;
	d->j++;
}

void	other_cases(struct s_data *d)
{
	d->ret_str[d->j] = d->str[d->i];
	d->i++;
	d->j++;
}
