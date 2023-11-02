/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:14:26 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 20:53:08 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			ft_one_split(t_data_split **data, t_args_list **args_list, char *input)
{
	if (!ft_add_arg_to_list(args_list, (*data)->tmp))
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

char		**ft_split_args(t_shell_data **shell_data, char *input)
{
	char		**res;
	size_t		len;
	t_args_list	*args_list;

	len = ft_strlen(input);
	args_list = ft_input_to_args_list(shell_data, input, len);
	res = ft_args_list_to_str_split(&args_list);
	ft_free_args_list(&args_list);
	if (!res)
		return (NULL);
	return (res);
}
