/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:18:21 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/14 09:40:10 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_init_all(t_shell_data **shell_data, char *shell_path, char *envp[])
{
	if (!ft_init_shell(shell_data, shell_path, envp))
	{
		perror("bash");
		return (0);
	}
	ft_init_shell_sigaction(*shell_data, MAIN);
	return (1);
}
