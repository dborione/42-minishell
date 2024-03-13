/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:52:52 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 16:50:48 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_heredoc_child(t_shell_data *shell_data, char *eof)
{
	char	*input;

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

int	ft_heredoc(t_shell_data *shell_data, char *eof)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		ft_memory_error(&shell_data);
	if (pid == 0)
		ft_heredoc_child(shell_data, eof);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	shell_data->exit_code = WEXITSTATUS(status);
	return (1);
}
