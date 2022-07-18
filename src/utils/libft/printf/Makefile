# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/06 21:02:37 by changhle          #+#    #+#              #
#    Updated: 2022/05/25 00:42:34 by moabid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft
LIBFT_LIB = libft.a

NAME = libftprintf.a
FILES = ft_printf \
		percent_specifier \
		c_specifier \
		s_specifier \
		dui_specifier \
		pxX_specifier \
		others
BONUS = ft_printf_bonus \
		percent_specifier_bonus \
		c_specifier_bonus \
		s_specifier_bonus \
		dui_specifier_bonus \
		pxX_specifier_bonus \
		others_bonus


ifdef WITH_BONUS
	OBJS_FILES = $(OBJS) $(OBJS_BONUS)
else
	OBJS_FILES = $(OBJS)
endif

all : $(NAME)

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_BONUS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(BONUS)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_BONUS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(BONUS)))

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(NAME) : $(OBJS_FILES)
	make -C ./libft --silent
	cp ../$(LIBFT_LIB) $(NAME)
	ar rcs $(NAME) $(OBJS_FILES)

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

$(OBJS_BONUS) : $(SRCS_BONUS)
	$(CC) $(CFLAGS) -c $(SRCS_BONUS)

bonus : $(OBJS_BONUS)
	make WITH_BONUS=1 all

clean :
	@echo "LIBFT deleted"
	@echo "LIBFTPRINTF deleted"
	@make -C $(LIBFT) clean
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re : fclean all

.PHONY : all clean fclean re bonus
