/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:46:09 by moabid            #+#    #+#             */
/*   Updated: 2022/09/08 12:05:51 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

t_env *export_the_argv(char **argv, t_env *enviroment)
{
	t_env *new;
	int i;

	i = 0;
	while(argv[i])
	{
		if(is_a_valid_identifier(argv[i]))
		{
			new = new_node();
			fill_new_node(argv[i], new);
			enviroment = append_new_node(enviroment, new);
		}
		else
		{
			ft_putstr_fd(argv[i],1);
			write(1," not a valid identifier\n", 24);
		}
		i++;
	}
	return (enviroment);
}

void ft_export (char **argv, struct minishell *minishell)
{
	t_env	*enviroment;
	t_env	*head;
	
	enviroment = minishell->env;
	enviroment = alphabetic_order(enviroment);
	head = enviroment;
	if(!argv[1])
	{
		print_the_enviroment(enviroment);
		exit(0);
	}
	else
	{
		head = export_the_argv(argv, enviroment);
		if(!head)
			exit(0);
	}
	enviroment = alphabetic_order(head);
	exit(0);
}

/************** TO DO LIST *****************/

// Solution 1 !

//int export(char **env, ...)

// char **comand_statement = {"a", "0"};
// char **comand_statement2 = {"z", "10"};

// export(minishll->g_ev, command_statment1, cmmand_statement2);

// Solutioon 2 !
// in export(char **env, char **statements);

// char **statement = { "a=0, z=10"};
// int cd (char **env)

// ------------>
// 	|------->

// terminate_process(pid);
