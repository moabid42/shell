NAME 		= minishell

SOURCES 	= $(shell find . -name "*.c")
HEADERS 	= $(shell find . -name "*.h")

OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))
DEPENDS 	= $(patsubst %.c, %.d, $(SOURCES))

CFLAGS 		= -g -Wall
RLFLAGS 	= -lreadline

all: $(NAME)

%.o: %.c
	@$(CC) -Iincludes $(CFLAGS) -MMD -MP -c $< -o $@

$(NAME): $(OBJECTS)
	@echo "Dependencies Compiled !"
	@$(CC) $(CFLAGS) $(RLFLAGS) -I $(OBJECTS) -o $(NAME)
	@echo "Compiled !"

clean:
	-@$(RM) $(OBJECTS) $(DEPENDS)
	-@$(RM) $(OBJECTS)
	@echo "Everything is Cleaned !"

fclean: clean
	-@$(RM) $(NAME)

test:
	@$(shell ./esh_tester.sh) 

run: all
	./$(NAME)

re: clean all

.PHONY: re run fclean clean all

-include $(DEPENDS)