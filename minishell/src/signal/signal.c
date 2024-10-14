#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

int	*get_signal(void)
{
	static int	g_signal = 0;

	return (&g_signal);
}

void	handle_sigquit(int sig)
{
	*get_exit_status() = 128 + sig;
	if (*get_signal() == EXEC_SIG)
	{
		printf("Quit : %d\n", sig);
		rl_replace_line("", 0);
	}
}

void	signal_base(void)
{
	if (*get_signal() == EXEC_SIG)
		signal(SIGQUIT, handle_sigquit);
	else
		signal(SIGQUIT, SIG_IGN);
}

void	handle_signal(int signo)
{
	*get_exit_status() = 128 + signo;
	if (*get_signal() == HEREDOC_SIG)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (*get_signal() == PROMT_SIG)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (*get_signal() == EXEC_SIG)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
