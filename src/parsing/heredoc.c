/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:52:52 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/24 15:54:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_heredoc(t_shell_data *shell_data, char *line)
{
    pid_t	pid;
	char    *eof;
    char    *input;
    int     status;

    pid = fork();
    if (pid < 0)
        perror("bash");
    if (pid == 0)
    {
        ft_init_shell_sigaction(shell_data, HEREDOC_CHILD);
        input = readline("> ");
        if (!input)
            exit(0);
        eof = line;
        while (!ft_isequal(eof, input))
        {
            free(input);
            input = readline("> ");
            if (!input)
                exit(0);
        }
        free(input);
    }
	//signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    shell_data->exit_code = WEXITSTATUS(status);
    return (1);
}
