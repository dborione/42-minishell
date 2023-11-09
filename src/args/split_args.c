/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:14:26 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/09 11:12:10 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			ft_one_split(t_data_split **data, t_args_list **args_list, char *input, char *tmp)
{
	if (!ft_add_arg_to_list(args_list, tmp))
	{
		ft_exit_split_args(data, args_list);
		return (0);
	}
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->start = (*data)->i;
	(*data)->space = 1;
	(*data)->tmp[0] = '\0';
	return (1);
}

t_args_list		*ft_split_args(t_shell_data **shell_data, char *input)
{
	size_t		len;
	t_args_list	*args_list;

	len = ft_strlen(input);
	args_list = ft_input_to_args_list(shell_data, input, len);
	if (!args_list)
		return (NULL);
	return (args_list);
}
