/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:46:09 by moabid            #+#    #+#             */
/*   Updated: 2022/10/25 12:17:24 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

static void print_the_enviroment(t_env *list)
{
	while(list)
	{
		write(1, "declare -x ", 11);
		ft_putstr_fd(list->name, 1);
		if(list->content != NULL)
		{
			write(1, "=\"", 2);
			ft_putstr_fd(list->content, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		list = list->next;
	}
}

bool	is_a_valid_identifier(char *str)
{
	int i;
	int j;
	char *invalid_char;

	invalid_char = (char *) "#@&*}{!?-+";
	i = 0;
	if (str[0] == '=')
		return (false);
	while(str[i])
	{
		j = 0;
		while(invalid_char[j] && invalid_char[j] != str[i])
			j++;
		if (invalid_char[j])
			return (false);
		i++;
	}
	if (ft_isdigit(str[0]))
		return (false);
	else
		return (true);
}

bool	indentfier_exist(t_env *env, char *str)
{
	char	**tokens;
	
	while(env)
	{
		if (my_strcmp(env->name, ft_split(str, '=')[0]) == 0)
		{
			tokens = ft_split(str, '=');
			if (tokens[1] == NULL)
				env->content = "";
			else
				env->content = tokens[1];
			return (true);
		}
		env = env->next;
	}
	return (false);
}

t_env *export_the_argv(struct minishell *minishell, char **argv, t_env *enviroment)
{
	t_env *new;
	int i;

	i = 1;
	while(argv[i])
	{
		if (is_a_valid_identifier(argv[i])
			&& indentfier_exist(enviroment, argv[i]) == true)
			;
		else if(is_a_valid_identifier(argv[i]))
		{
			new = new_node();
			fill_new_node(argv[i], new);
			enviroment = append_new_node(enviroment, new);
		}
		else
		{
			dprintf(2, "esh: export: `%s': not a valid identifier\n", argv[i]);
			minishell->return_value = 1;
		}
		i++;
	}
	return (enviroment);
}

static bool check_empty_args(char **argv)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(argv[i])
	{
		j = 0;
		while(argv[i][j])
		{
			if((bool)ft_isspace(argv[i][j]) == false)
				return(false);
			j++;
		}
		i++;
	}
	return (true);
}

void ft_export (char **argv, struct minishell *minishell)
{
	t_env	*enviroment;
	t_env	*head;
	
	enviroment = minishell->env;
	enviroment = alphabetic_order(enviroment);
	head = enviroment;
	if(argv[1] == NULL || check_empty_args(argv) == false)
		print_the_enviroment(enviroment);
	else
	{
		head = export_the_argv(minishell, argv, enviroment);
		if(!head)
			exit(0);
	}
	enviroment = alphabetic_order(head);
}
