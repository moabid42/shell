
#include "minishell.h"

bool    minishell_create(struct minishell *minishell)
{
	// here we are gonna do smth that I don't know yet

}

bool    minishell_init(struct minishell *minishell)
{
    // here we are gonna init the file descriptors and so on 
}

void	minishell_loop(struct minishell *minishell)
{
	readline(0);
	while (1)
	{
		if (signal_is_thrown() == true)
			break;
		minishell_start(minishell);
	}
}

bool    minishell_run(struct minishell *minishell)
{
	//// here where we are gonna have all our code /// 
	/// bla bla bla 
	if (minishell_init(minishell))
		minishell_loop(minishell);

}

void    minishell_destroy(struct minishell *minishell)
{
	// here we are gonna terminate all the processes and free all the leaks 

}

int main(int argc, char **argv)
{
    struct minishell minishell;

    if (argc > 1)
        ft_error(SYNTAX_ERROR);
    if (minishell_create(&minishell))
        if (minishell_run(&minishell))
            minishell_destroy(&minishell);
    return (0);
}