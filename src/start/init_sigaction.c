#include "../../inc/minishell.h"

void    ft_handle_sig_act(int sig, siginfo_t *info, void *shell_data)
{
    t_shell_data *tmp_shell_data;

    tmp_shell_data = shell_data;
    //readline("\n> ");
	// free((*tmp_shell_data).prompt);
	//ft_get_input(&tmp_shell_data);
	if (sig == SIGINT)
	{
    	ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (info || !tmp_shell_data)
		return ;
}

void    ft_init_shell_sigaction(t_shell_data *shell_data)
{
    shell_data->sa.sa_sigaction = &ft_handle_sig_act; // envoyer pid
    sigemptyset(&shell_data->sa.sa_mask);
    shell_data->sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &(shell_data->sa), NULL);
}