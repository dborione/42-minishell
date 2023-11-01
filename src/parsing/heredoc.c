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

    // if (pipe(shell_data->pipe) == -1)
	// 	perror("bash");
    shell_data->quit = 1;
    pid = fork();
    if (pid < 0)
    {
        // close(shell_data->pipe[READ_PIPE]);
		// close(shell_data->pipe[WRITE_PIPE]);
        perror("bash");
    }
    if (pid == 0)
    {
        // close(shell_data->pipe[READ_PIPE]);
		shell_data->rl_catch_signals = 0;
        ft_init_shell_sigaction(shell_data, HEREDOC_CHILD);
        input = readline("> ");
        if (!input)
        {
            //shell_data->quit = 1;
            // write(shell_data->pipe[WRITE_PIPE],&(shell_data->quit), sizeof(shell_data->quit));
	        // close(shell_data->pipe[WRITE_PIPE]);
            exit(0);
        }
        eof = line;
        while (!ft_isequal(eof, input))
        {
            free(input);
            input = readline("> ");
            if (!input)
            {
                //kill(pid, SIGTERM);
                //shell_data->quit = 1;
                // write(shell_data->pipe[WRITE_PIPE],&(shell_data->quit), sizeof(shell_data->quit));
	            // close(shell_data->pipe[WRITE_PIPE]);
                exit(0);
            }
        }
	    //close(shell_data->pipe[WRITE_PIPE]);
        free(input);
    }
    // read(shell_data->pipe[READ_PIPE], &(shell_data->quit), sizeof(shell_data->quit));
	// close(shell_data->pipe[WRITE_PIPE]);
    // close(shell_data->pipe[READ_PIPE]);
    // return (waitpid(pid, NULL, WNOHANG));
	//signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    shell_data->exit_code = WEXITSTATUS(status);
    return (1);
}
