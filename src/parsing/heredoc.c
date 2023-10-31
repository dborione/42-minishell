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
    pid_t	parent;
	char    *eof;
    char    *input;
    // int     pipe_fd[2];

    // if (pipe(pipe_fd) == -1)
	// 	perror("bash");
    //ft_init_shell_sigaction(shell_data);
    ft_init_shell_sigaction(shell_data, HEREDOC_PARENT);
    parent = fork();
    if (parent < 0)
    {
        // close(pipe_fd[READ_PIPE]);
		// close(pipe_fd[WRITE_PIPE]);
        perror("bash");
    }
    if (parent == 0)
    {
        // kill(parent, SIGINT);
        ft_init_shell_sigaction(shell_data, HEREDOC_CHILD);                                                                    
        //signal(SIGINT, SIG_DFL);
        //signal(SIGQUIT, SIG_DFL);
        // close(pipe_fd[READ_PIPE]);
        input = readline("> ");
        if (!input)
        {
	        // close(pipe_fd[WRITE_PIPE]);
            return (0);
        }
        eof = line;
        while (!ft_isequal(eof, input))
        {
            free(input);
            input = readline("> ");
            if (!input)
            {
	            // close(pipe_fd[WRITE_PIPE]);
                return (0);
            }
        }
        free(input);
    }
    waitpid(parent, NULL, 0);
	// close(pipe_fd[WRITE_PIPE]);
    if (!shell_data){

    }
    return (0);
}