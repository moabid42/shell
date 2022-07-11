
#include "minishell.h"

bool    minishell_create(struct minishell *minishell)
{

}

bool    minishell_parse(struct minishell *minishell)
{
    
}

bool    minishell_run(struct minishell *minishell)
{

}

void    minishell_destroy(struct minishell *minishell)
{

}

int main(int argc, char **argv)
{
    struct minishell *minishell;

    if (argc > 1)
        ft_error(SYNTAX_ERROR);
    if (minishell_create(&minishell))
        if (minishell_parse(&minishell))
            if (minishell_run(&minishell))
                minishell_destroy(&minishell);
    return (0);
}