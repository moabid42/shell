/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:59:16 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 02:28:33 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

char	*parser(char *cmd, char *paths)
{
	char	*with_slash;
	char	*l_path;
	char	*path;

	with_slash = ft_strrchr(cmd, '/');
	if (with_slash)
	{
		path = ft_strjoin(paths, with_slash);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
	}
	else
	{
		l_path = ft_strjoin(paths, "/");
		path = ft_strjoin(l_path, cmd);
		free(l_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
	}
	free(path);
	return (NULL);
}

void	freeme(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

// bool	ft_iscommand(char *str, char **env)
bool	ft_iscommand(char *str, t_env *env)
{
	if (get_path(str, env))
		return (true);
	return (false);
}

bool	ft_isfile(char *str)
{
	if (access(str, F_OK))
		return (true);
	return (false);
}

bool	ft_isword(char *str)
{
	int i;

	i = 0;
	if(str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void	minishell_error(struct minishell *minishell, char *str)
{
	minishell->return_value = 1;
}

int	my_strcmp(const char *strg1, char *strg2)
{
	if ((strg1 == NULL && strg2 == NULL))
		return (0);
	else if (!strg1 || !strg2)
		return (1);
	while ((*strg1 != '\0' && *strg2 != '\0') && *strg1 == *strg2)
	{
		strg1++;
		strg2++;
	}
	if (*strg1 == *strg2)
		return (0);
	else
		return (*strg1 - *strg2);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr)
		ft_bzero(ptr, size);
	else
	{
		free(ptr);
		exit(1);
	}
	return (ptr);
}

unsigned int	ft_get_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	if (nb_strs == 0)
		return (1);
	return (nb_strs);
}

int	ft_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r' \
	|| c == '\t' || c == '\v' || c == ' ');
}

bool	node_contain_special_single(char *str, int c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] == ' ')
			return (true);
		i++;
	}
	return (false);
}

bool	node_contain_special(char *str, int c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		if (count == 2)
			return (true);
		i++;
	}
	return (false);
}

char	*ft_special_trim(char *str, int c, int size)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_malloc(sizeof(char) * (size - i));
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[ft_strlen(new)] = '\0';
	return (new);
}

int	error_exit(struct minishell *minishell, char *str, char *var, int exit_code)
{
	if (var == NULL)
		write(2, str, ft_strlen(str));
	else
	{
		write(2, str, ft_strlen(str));
		write(2, var, ft_strlen(var));
		write(2, "\'\n", 2);
	}
	minishell->return_value = exit_code;
	return (true);
}

struct ast	*error_exit_null(struct minishell *minishell, char *str, char *var, int exit_code)
{
	if (var == NULL)
		write(2, str, ft_strlen(str));
	else
	{
		write(2, str, ft_strlen(str));
		write(2, var, ft_strlen(var));
		write(2, "\'\n", 2);
	}
	minishell->return_value = exit_code;
	return (NULL);
}
