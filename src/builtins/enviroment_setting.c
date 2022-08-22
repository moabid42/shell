/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_setting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:04:04 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/22 12:12:01 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


char *copy_till_bit(char *str, int n_byte)
{
	int i;
	char *str_cp;

	str_cp = malloc(n_byte + 1);
	if(str_cp == NULL)
		return NULL;
	i = 0;
	while(str[i] && i < n_byte)
	{
		str_cp[i] = str[i];
		i++;
	}
	str_cp[n_byte] = '\0';
	return (str_cp);
}

char **split_name_content(char *str)
{
	char **split;
	int i;

	i = 0;
	split = malloc(sizeof(char *) * 3);
	if(split == NULL)
		return(NULL);
	split[0] = copy_till_bit(str, find_chr(str, '='));
	split[1] = copy_till_bit(&str[find_chr(str, '=') + 1], ft_strlen(str) - find_chr(str, '='));
	split[2] = NULL; 
	return (split);
}

t_env *create_the_env(char **env)
{
	t_env	*head;
	t_env	*list;
	char **split;
	int i;
	
	i = 0;
	head = malloc(sizeof(t_env));
	list = head;
	while(env[i])
	{
		split = split_name_content(env[i]);
		list->name = split[0];
		list->content = split[1];
		if(env[i+1])
		{
			list->next = new_node();
			list = list->next;
		}
		else
			list->next = NULL;
		i++;
	}
	return (head);
}

//int	export(**arg, **env);

// int main (int argc, char **argv, char **env)
// {
// // 	int i;
// //  	t_env *enviroment;
// // // 	i = 0;
// // // 	// while(env[i])
// // // 	// {	
// // // 	// 	printf("%d : %s \n", i, env[i]);
// // // 	// 	i++;
// // // 	// }
//   	enviroment = create_the_env(env);
//  	while(enviroment != NULL)
//  	{
//  		printf("name: |%s|    content: |%s| \n", enviroment->name, enviroment->content);
//  		enviroment = enviroment->next;
//  	}
// }