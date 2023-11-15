/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:52:52 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/09 14:13:22 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_heredoc(t_shell_data *shell_data, char *eof)
{
    pid_t	pid;
    char    *input;
    int     status;

    pid = fork();
    if (pid < 0)
		ft_memory_error(&shell_data);
    if (pid == 0)
    {
        ft_init_shell_sigaction(shell_data, HEREDOC_CHILD);
        input = readline("> ");
        if (!input)
            exit(0);
        while (!ft_isequal(eof, input))
        {
            free(input);
            input = readline("> ");
            if (!input)
                exit(0);
        }
        free(input);
        exit(0);
    }
    signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    shell_data->exit_code = WEXITSTATUS(status);
    return (1);
}
