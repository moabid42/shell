NAME 		= minishell

SOURCES 	= $(shell find . -name "*.c")
HEADERS 	= $(shell find . -name "*.h")

OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))
DEPENDS 	= $(patsubst %.c, %.d, $(SOURCES))

CFLAGS = -g -Wall

all: $(NAME)

%.o: %.c
	@$(CC) -Iincludes $(CFLAGS) -MMD -MP -c $< -o $@

$(NAME): $(OBJECTS)
	@echo "Dependencies Compiled !"
	@$(CC) -Iincludes $(OBJECTS) $(LDFLAGS) -o $(NAME)
	@echo "Compiled !"

clean:
	-@$(RM) $(OBJECTS) $(DEPENDS)
	@echo "Everything is Cleaned !"

fclean: clean
	-@$(RM) $(NAME)

run: all
	$(NAME)

re: clean all

.PHONY: re run fclean clean all

-include $(DEPENDS)