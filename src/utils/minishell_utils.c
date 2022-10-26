/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:16:01 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:20:14 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_chr(char *str, char append)
{
	char	*new_str;
	int		i;

	if (str == NULL)
		return (NULL);
	new_str = ft_malloc(ft_strlen(str) + 2);
	if (new_str != NULL)
	{
		i = 0;
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = append;
		new_str[i + 1] = '\0';
	}
	free(str);
	return (new_str);
}

char	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

int	ft_strlen_newline(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] > 31 && str[i] < 127)
		i++;
	return (i);
}

bool	is_weirdo(char *input_line, struct s_minishell *minishell)
{
	if (!my_strcmp(input_line, "<<")
		|| !my_strcmp(input_line, "<>")
		|| !my_strcmp(input_line, "<")
		|| !ft_strncmp(input_line, "<> &&", 5)
		|| (input_line[ft_strlen(input_line) - 1] == '|'
			&& input_line[ft_strlen(input_line) - 2] != '|')
		|| input_line[ft_strlen(input_line) - 1] == '>')
		error_exit(minishell, "esh: syntax error near unexpected token \
		`newline'\n", NULL, 258);
	else if (!my_strcmp(input_line, ">>>>>")
		|| !my_strcmp(input_line, ">> >> >> >>"))
		error_exit(minishell, "esh: syntax error near unexpected token \
		`>>'\n", NULL, 258);
	else if (!my_strcmp(input_line, "> > > > >"))
		error_exit(minishell, "esh: syntax error near unexpected token \
		`>'\n", NULL, 258);
	else if (!my_strcmp(input_line, "<<<<<<"))
		error_exit(minishell, "esh: syntax error near unexpected token \
		`<<<'\n", NULL, 258);
	else if (!my_strcmp(input_line, "< < < < < <"))
		error_exit(minishell, "esh: syntax error near unexpected token \
		`<'n", NULL, 258);
	else if (!my_strcmp(input_line, "()"))
		error_exit(minishell, "syntax error near unexpected token \
		`)'\n", NULL, 258);
	else
		return (false);
	return (true);
}
