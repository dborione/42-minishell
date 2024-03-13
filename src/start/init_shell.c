/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:40:14 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 16:04:45 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_init_defaults(t_shell_data **shell_data)
{
	*shell_data = malloc(sizeof(t_shell_data));
	if (!shell_data || !(*shell_data))
		return (0);
	(*shell_data)->envp = NULL;
	(*shell_data)->private_envp = NULL;
	(*shell_data)->pwd = NULL;
	(*shell_data)->home = NULL;
	(*shell_data)->cmds = NULL;
	(*shell_data)->input_target_fd = STDIN_FILENO;
	(*shell_data)->input_fd = STDIN_FILENO;
	(*shell_data)->output_source_fd = STDOUT_FILENO;
	(*shell_data)->output_fd = STDOUT_FILENO;
	(*shell_data)->infile = 0;
	(*shell_data)->outfile = 0;
	(*shell_data)->exit_code = 0;
	(*shell_data)->exit = 0;
	(*shell_data)->prompt = NULL;
	return (1);
}

int	ft_init_shell(
	t_shell_data **shell_data, char *envp[], char *shell_path
)
{
	if (!ft_init_defaults(shell_data))
		return (0);
	if (!ft_init_envp(shell_data, envp, shell_path))
		return (0);
	return (1);
}
