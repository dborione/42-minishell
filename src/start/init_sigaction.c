#include "../minishell.h"

void    ft_handle_sig_act(int sig)
{
    sig = 1; //pour la norm
    ft_putstr_fd("\n", STDOUT_FILENO);
}

void    ft_init_shell_sigaction(t_shell_data *shell_data)
{
    shell_data->sa.sa_handler = &ft_handle_sig_act; // envoyer pid
    shell_data->sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &(shell_data->sa), NULL);
    ft_get_input(&shell_data);
}