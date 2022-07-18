/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:38:24 by sthitiku          #+#    #+#             */
/*   Updated: 2022/05/25 14:32:25 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_read
{
	int				fd;
	char			*str;
	struct s_read	*next;
}				t_read;

size_t	ft_strlen1(char *s);
void	ft_strlcpy1(char *dst, char *src, size_t dstsize);
char	*get_next_line(int fd);
int		new_line_checker(char *s);
t_read	*init_struct(int fd);
t_read	*check_fd(t_read *read, int fd);
t_read	*clear_head(t_read *read, int fd);
char	*free_and_cpy_reminder(char *str);
char	*return_line(char *str);
char	*read_file(int fd, char *str);

#endif
