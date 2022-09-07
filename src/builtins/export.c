#include "builtins.h"

static void print_the_enviroment(t_env *list)
{
	while(list)
	{
		write(1, "declare -x ", 11);
		ft_putstr_fd(list->name, 1);
		if(list->content != NULL)
		{
			write(1, "=\"", 2);
			ft_putstr_fd(list->content, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		list = list->next;
	}
}
/*  PAY ATTENTION IT ILL TELL YOU ONLY IF STR1 COME FIRST THEN str2 so if STR1 < STR2*/

// static bool	check_the_arg(char *str)
// {
// 	int	i;
	
// 	i = 0;
// 	if(str[0] == '_')
// 	{
// 		if(ft_isdigit(str[1]))
// 			return (false);
// 		i++;
// 	}
// 	else
// 	{
// 		if(ft_isdigit(str[0]))
// 			return (false);
// 	}
// 	/*ASK MOUAD*/
// 	// if(str[0] == '$') 
// 	// {
// 	// 	if(check_the_arg(&variablestoredin(&str[1])))
// 	// 		return (true);
// 	// }
// 	while(str[i])
// 	{
// 		if(check_string(str[i],"~#$&*(){}\\|[];'<>\"/?!"))
// 			return(false);
// 	}
// 	return (true);
// }


t_env *export_the_argv(char **argv, t_env *enviroment)
{
	t_env *new;
	int i;

	i = 0;
	while(argv[i])
	{
		// if(check_the_arg(argv[i]))
		// {
			new = new_node();
			fill_new_node(argv[i], new);
			enviroment = append_new_node(enviroment, new);
		// }
		// else
		// 	return (NULL);
		i++;
	}
	return (enviroment);
}

void ft_export (int argc, char **argv, struct minishell *minishell)
{
	t_env	*enviroment;
	t_env	*head;
	
	//enviroment = create_the_env(minishell->env);
	enviroment = minishell->env;
	enviroment = alphabetic_order(enviroment);
	head = enviroment;
	if(argc == 1)
	{
		print_the_enviroment(enviroment);
		exit(0);
	}
	if(argc > 1)
	{
		head = export_the_argv(argv, enviroment);
		if(!head)
			exit(0);
	}
	enviroment = alphabetic_order(head);
	//print_the_enviroment(enviroment);
	exit(0);

	//check_the_input(argc,argv);
}

/************** TO DO LIST *****************/

// Solution 1 !

//int export(char **env, ...)

// char **comand_statement = {"a", "0"};
// char **comand_statement2 = {"z", "10"};

// export(minishll->g_ev, command_statment1, cmmand_statement2);

// Solutioon 2 !
// in export(char **env, char **statements);

// char **statement = { "a=0, z=10"};
// int cd (char **env)

// ------------>
// 	|------->

// terminate_process(pid);
