/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborione <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:22:32 by dborione          #+#    #+#             */
/*   Updated: 2023/11/17 17:23:00 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_dup2_error(t_shell_data **shell_data, int pipe)
{
	ft_perror("bash: dup2: Bad file descriptor\n");
	if (pipe == TRUE)
		return (0);
	(*shell_data)->exit_code = 127;
	exit (1);
}
