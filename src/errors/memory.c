/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:56:02 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:56:29 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_memory_error(t_shell_data **shell_data)
{
	ft_perror("bash: fork: Cannot allocate memory");
	(*shell_data)->exit_code = 127;
}
