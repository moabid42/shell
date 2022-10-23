/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enviroment_setting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:04:04 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/23 16:28:33 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

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
	split = malloc(sizeof(char *) * 3);
	if(split == NULL)
		return(NULL);
	split[0] = copy_till_bit(str, find_chr(str, '='));
	split[1] = copy_till_bit(&str[find_chr(str, '=') + 1], ft_strlen(str) - find_chr(str, '='));
	split[2] = NULL; 
	return (split);
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
	return (enviroment);
}
