/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:08:16 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 01:29:53 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_shell_data **shell_data, char *input)
{
	char **args;

	args = ft_split(input, ' ');
	if (!args)
		return (-1);
	if (args[1])
	{
		ft_putendl_fd("bash: exit: vous donnez trop d'arguments !", 2);
		return (0);
	}
	(*shell_data)->exit = 1;
	return (1);
}