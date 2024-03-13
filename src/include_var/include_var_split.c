/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_var_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:06:42 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 18:19:00 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_include_var_split(t_args_list **args, char **var_split)
{
	size_t	i;

	if (!var_split[0])
	{
		ft_free_split(var_split);
		return (1);
	}
	i = 1;
	while (var_split[i])
	{
		if (!ft_add_arg_to_list(args, var_split[i]))
		{
			ft_free_split(var_split);
			return (0);
		}
		i++;
	}
	ft_free_split(var_split);
	return (1);
}
