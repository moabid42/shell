/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:35:26 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:25:07 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_reader(int fd_in)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd_in);
		if (line == NULL)
			break ;
		printf("%s", line);
	}
	printf("\n");
}

void	rise_error_and_exit(struct s_ast *ast)
{
	dprintf(2, "esh: %s: No such file or directory\n",
		ast->left->value.token_name);
	exit(1);
}

void	print_file(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY, 0777);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
}

void	new_line_remove(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
		i++;
	line[i] = '\0';
}

int	ast_child_num(struct s_ast *node)
{
	int			num;
	struct s_ast	*tmp;

	num = 0;
	tmp = node;
	if (tmp->right)
		num++;
	while (tmp->left)
	{
		num++;
		tmp = tmp->left;
	}
	return (num);
}
