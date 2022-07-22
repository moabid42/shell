NAME 	= 	libft.a
CFLAGS 	= 	-Wall -Wextra -Werror
RM 		= 	rm -f
AR 		= 	ar crs

YELLOW	=	\033[1;33m
NC		=	\033[0m
GREEN	=	\033[0;32m
RED		=	\033[0;31m

FILES 	= 	ft_isalpha \
			ft_isdigit \
			ft_isascii \
			ft_isalnum \
			ft_isprint \
			ft_strlen \
			ft_memset \
			ft_bzero \
			ft_memcpy \
			ft_memmove \
			ft_strlcpy \
			ft_strlcat \
			ft_toupper \
			ft_tolower \
			ft_strchr \
			ft_strrchr \
			ft_strncmp \
			ft_memchr \
			ft_memcmp \
			ft_strnstr \
			ft_atoi \
			ft_calloc \
			ft_strdup \
			\
			ft_substr \
			ft_strjoin \
			ft_strtrim \
			ft_split \
			ft_itoa \
			ft_strmapi \
			ft_striteri \
			ft_putchar_fd \
			ft_putstr_fd \
			ft_putnbr_fd \
			ft_putendl_fd \
		 	ft_lstnew \
	  		ft_lstadd_front \
	  		ft_lstsize \
	  		ft_lstlast \
	  		ft_lstadd_back \
	  		ft_lstdelone \
	  		ft_lstclear \
			ft_lstiter \
			ft_lstmap \
			get_next_line \
			get_next_line_utils

all: $(NAME)

SRCS_DIR = ./
CFILES = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OFILES = ${CFILES:.c=.o}

${NAME} : ${OFILES} ${INC}
	@ar -rcs ${NAME} ${OFILES}
	@echo "${YELLOW}libft.a created 👍${NC}"

%.o:%.c
	@${CC} ${CFLAGS} -o $@ -c $<

clean:
	@rm -f ${OFILES} ${OBONUS}

fclean : clean
	@rm -f ${NAME}
	@echo "${YELLOW}libft.a is removed 👎${NC}"

re : fclean all


.PHONY: all clean fclean re bonus norm