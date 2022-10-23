/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_sig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:14:59 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 17:15:37 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	termios_echoback(bool echo_ctl_chr)
{
	struct termios	terminos_p;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (1);
	terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (1);
	return (0);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		// minishell->return_value = 1;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();//Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
		rl_replace_line("", 0);//removes the content of the line with texts which is "" here
		rl_redisplay(); //Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
	}
}

void	signal_run(int sig)
{
	struct sigaction	sig_action;

	sig_action.sa_handler = handler;
	if (sigaction(sig, &sig_action, NULL) == -1)
		return ;
	sigaction(SIGINT, &sig_action, NULL);
	signal(SIGQUIT, SIG_IGN);
}
