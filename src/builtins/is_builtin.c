/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:28:14 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/24 15:54:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_builtin(char *input)
{
	// espaces?
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
