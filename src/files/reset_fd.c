/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:08:28 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 17:14:04 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_reset_fd(t_shell_data **shell_data)
{
	(*shell_data)->infile = 0;
	(*shell_data)->outfile = 0;
	(*shell_data)->input_fd = STDIN_FILENO;
	(*shell_data)->output_fd = STDOUT_FILENO;
}
