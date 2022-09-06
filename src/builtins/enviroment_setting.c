/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_setting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:04:04 by frmessin          #+#    #+#             */
/*   Updated: 2022/09/06 07:11:25 by moabid           ###   ########.fr       */
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
	// int i;

	// i = 0;
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
	while(env[i]!= NULL)
	{
		split = split_name_content(env[i]);
		list->name = split[0];
		list->content = split[1];
		if(env[i+1]!= NULL)
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

int list_len(t_env *env)
{
	t_env *tmp;
	tmp = env;
	int i;

	i = 0;
	while(tmp != NULL)
	{
		tmp= tmp->next;
		i++;
	}
	return (i);
}

static char *make_env_string(t_env *env)
{
	char *string;
	int i;
	int j;
	
	string = malloc(sizeof(char) * ft_strlen(env->name) + ft_strlen(env->content) + 2);
	if(!string)
		return NULL;
	string[ft_strlen(env->name) + ft_strlen(env->content) + 1] = '\0';

	i = 0;
	while((env->name)[i])
	{
		string[i] = (env->name)[i];
		i++;
	}
	string[i] = '=';
	i++;
	j = 0;
	while((env->content)[j])
	{
		string[i] = (env->content)[j];
		j++;
		i++;
	}
	return(string);
}

char **env_to_string(t_env *env)
{
	t_env *tmp;
	tmp = env;
	char **enviroment;
	int i;

	enviroment = malloc (sizeof(char *) * (list_len(env) + 1));
	if(!enviroment)
		return NULL;
	enviroment[list_len(env)] = NULL;
	i = 0;
	while(i < list_len(env))
	{
		enviroment[i] = make_env_string(tmp);
		i++;
		tmp=tmp->next;
	}
	i = 0;
	// while(enviroment[i])
	// {
	// 	printf(" int i :%d, %s\n", i, enviroment[i]);
	// 	i++;
	// }
	return (enviroment);
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