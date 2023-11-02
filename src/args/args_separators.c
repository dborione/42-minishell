/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_separators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:16:55 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 20:49:59 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_invalid_args_separator(t_shell_data **shell_data, char *input)
{
	if (ft_startswith(input, "||")
		|| ft_startswith(input, "<<<")
		|| ft_startswith(input, ">>>")
		)
	{
		ft_wrong_tokens_syntax(shell_data, input[0]);
		return (1);
	}
	return (0);
}

int	ft_split_char_separator(
	t_data_split **data, t_args_list **args_list, char *input, char separator)
{
	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	if (!(*data)->space && (*data)->tmp[0])
	{
		if (!ft_join_args(args_list, (*data)->tmp))
			return (0);
		(*data)->tmp[0] = '\0';
	}
	else if ((*data)->tmp[0] && !ft_one_split(data, args_list, input) && (*data)->tmp[0])
		return (0);
	(*data)->tmp[0] = separator;
	(*data)->tmp[1] = '\0';
	if (!ft_one_split(data, args_list, input))
		return (0);
	(*data)->i++;
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->space = 1;
	(*data)->start = (*data)->i;
	return (1);
}

int	ft_split_string_separator(
	t_data_split **data, t_args_list **args_list, char *input, char *separator)
{
	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	if (!(*data)->space && (*data)->tmp[0])
	{
		if (!ft_join_args(args_list, (*data)->tmp))
			return (0);
		(*data)->tmp[0] = '\0';
	}
	else if ((*data)->tmp[0] && !ft_one_split(data, args_list, input) && (*data)->tmp[0])
		return (0);
	(*data)->tmp[0] = separator[0];
	(*data)->tmp[1] = separator[1];
	(*data)->tmp[2] = '\0';
	if (!ft_one_split(data, args_list, input))
		return (0);
	(*data)->i++;
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->space = 1;
	(*data)->start = (*data)->i;
	return (1);
}
