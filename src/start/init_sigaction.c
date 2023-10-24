#include "../minishell.h"

void    ft_handle_sig_act(int sig, siginfo_t *info, void *shell_data)
{
    t_shell_data *tmp_shell_data;

    // if (info)
    // {

    // }
    info = NULL; //norm
    sig = 1; //pour la norm
    tmp_shell_data = shell_data;
    //printf("aaaaaa");
    //ft_putstr_fd("\n", STDOUT_FILENO);
    //ft_get_input(&tmp_shell_data);
}

void    ft_init_shell_sigaction(t_shell_data *shell_data)
{
    shell_data->sa.sa_sigaction = &ft_handle_sig_act; // envoyer pid
    // shell_data->sa.sa_handler = &ft_handle_sig_act; // envoyer pid
    sigemptyset(&shell_data->sa.sa_mask);
    shell_data->sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &(shell_data->sa), NULL);
    //readline(ft_show_user_path(shell_data->envp));
}