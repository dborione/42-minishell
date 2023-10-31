#include "../../inc/minishell.h"

static
void    ft_handle_sig_act_heredoc_parent(int sig)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, 0, &term);
	if (sig == SIGINT)
		rl_redisplay();
}

static
void    ft_handle_sig_act_heredoc_child(int sig)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, 0, &term);
	if (sig == SIGINT)
	{
    	ft_putstr_fd("\n", STDOUT_FILENO);
		exit (0);
	}
}

static
void    ft_handle_sig_act_main(int sig)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, 0, &term);
	if (sig == SIGINT)
	{
    	ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void    ft_init_shell_sigaction(t_shell_data *shell_data, int process)
{
	// if (shell_data)
	// 	return ;

	// int	rl_catch_signals;
	// rl_catch_signals = 0; // peut etre necessaire pour le heredoc je vais voir
	if (process == MAIN)
    	shell_data->sa.sa_handler = &ft_handle_sig_act_main;
	if (process == HEREDOC_CHILD)
    	shell_data->sa.sa_handler = &ft_handle_sig_act_heredoc_child;
	if (process == HEREDOC_PARENT)
    	shell_data->sa.sa_handler = &ft_handle_sig_act_heredoc_parent;
    sigemptyset(&shell_data->sa.sa_mask);
	shell_data->sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &(shell_data->sa), NULL);
    shell_data->sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &(shell_data->sa), NULL);
}