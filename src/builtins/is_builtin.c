/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:28:14 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/23 12:03:23 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_builtin(char *input)
{
	if (ft_isequal(input, "cd") || ft_startswith(input, "cd "))
		return (1);
	if (ft_startswith(input, "pwd ") || ft_isequal(input, "pwd"))
		return (1);
	if (ft_startswith(input, "env ") || ft_isequal(input, "env"))
		return (1);
	if (ft_isequal(input, "echo") || ft_startswith(input, "echo "))
		return (1);
	if (ft_startswith(input, "export") || ft_isequal(input, "pwd"))
		return (1);
	if (ft_startswith(input, "unset") || ft_isequal(input, "env"))
		return (1);
	if (ft_startswith(input, "exit") || ft_isequal(input, "exit"))
		return (1);
	return (0);
}
