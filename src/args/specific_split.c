/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specific_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:43:39 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 15:15:54 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_space_split(t_data_split **data, t_args_list **args_list, char *input)
{
	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	if (!(*data)->space)
	{
		if (!ft_join_args(args_list, (*data)->tmp))
			return (0);
		(*data)->tmp[0] = '\0';
		// while (ft_isspace(input[(*data)->i]))
		// 	(*data)->i++;
		// (*data)->start = (*data)->i;
		// (*data)->space = 1;
		// (*data)->tmp[0] = '\0';
	}
	else if (!ft_one_split(data, args_list, input))
		return (0);
	(*data)->space = 1;
	return (1);
}

int	ft_quotes_split(t_data_split **data, t_args_list **args_list, char *input)
{
	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	if (!(*data)->space) // retirer la verif de l'espace
		(*data)->start = ft_split_from_quotes(*data, args_list, input);
	else
		(*data)->start = ft_join_from_quotes(args_list, (*data)->tmp, &input[(*data)->i]);
	if (!(*data)->start)
	{
		ft_exit_split_args(data, args_list);
		return (0);
	}
	(*data)->i += (*data)->start;
	if (!ft_isspace(input[(*data)->i]))
		(*data)->space = 0;
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->start = (*data)->i;
	(*data)->tmp[0] = '\0';
	return (1);
}

