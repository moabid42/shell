/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:05:01 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/20 12:14:08 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static	t_env *create_variable(t_env *env, char *name, char *path)
{
	t_env *new;
	
	new = new_node();
	new->name = name;
	new->content = path;
	env = append_new_node(env, new);
	return (env);
}

static bool		update_current_pwd(char *path, char *old_path, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while(tmp && !my_strcmp(tmp->name, "PWD"))
		tmp = tmp->next;
	if (tmp == NULL)
		*env = create_variable(*env, "PWD", path);
	else
	{
		if(tmp->content)
			free(tmp->content);
		tmp->content = path; 
	}
	tmp = *env;
	while(tmp && !my_strcmp(tmp->name, "OLDPWD"))
		tmp=tmp->next;
	if(tmp == NULL)
		*env = create_variable(*env, "OLDPWD", old_path);
	else
	{
		if(tmp->content)
			free(tmp->content);
		tmp->content = old_path;
	}
	return (true);
}

static DIR		*check_cd(int argc, char **argv, t_env *env)
{
	t_env	*tmp;
	DIR	*dir;

	tmp = env;
	if(argc == 1)
	{
		while(tmp && !my_strcmp(tmp->name, "HOME"))
			tmp=tmp->next;
		if (tmp == NULL)
		{
			write(1,"no HOME is setted",17);
			return (false);
		}
		dir = opendir(tmp->content);
	}
	dir = opendir(argv[1]);
	return (dir);
}
static char	*set_path(int argc, char **argv, t_env *env)
{
	t_env *tmp;
	
	tmp = env;
	if(argc == 1)
	{
		while(tmp && !my_strcmp(tmp->name, "HOME"))
			tmp=tmp->next;
		return (tmp->content);
	}
	else
		return(argv[1]);
}

int		ft_cd(int argc, char **argv, t_env *env)
{
	DIR		*dir;
	char	*old_path;
	char	*path;

	dir = check_cd(argc, argv, env);
	if (dir == NULL)
	{
		write(1, "wrong directory",15);
		return (0);
	}
	path = set_path(argc, argv, env);
	old_path = get_pwd();
	if (path && (chdir(path) == -1))
	{
		write(1, "wrong directory",15);
		return (0);
	}
	if (update_current_pwd(path, old_path, &env) == false)
		return (0);
	while(env != NULL)
 	{
 		printf("name: |%s|    content: |%s| \n", env->name, env->content);
 		env = env->next;
 	}
	return (0);
}

// int		main(int argc,	char **argv, char **env)
// {
// 	int		error;
// 	t_env	*enviroment;
// 	enviroment = create_the_env(env);
// 	error = ft_cd( argc, argv, enviroment);
// 	return (error);
// }