/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parse_res.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborione <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:03:44 by dborione          #+#    #+#             */
/*   Updated: 2023/11/17 17:03:46 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_set_res(t_shell_data **shell_data, int res)
{
	if (res > 0)
		return (1);
	else if ((*shell_data)->exit_code == SIGINT)
		return (SIGINT);
	return (-1);
}
