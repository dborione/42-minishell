/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_separators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:16:55 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 14:47:16 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_invalid_args_separator(char *input)
{
	if (ft_startswith(input, "||")
		|| ft_startswith(input, "<<<")
		|| ft_startswith(input, ">>>")
		)
	{
		ft_putstr_fd("bash: syntax error near unexpected token «", 2);
		ft_putchar_fd(input[0], 2);
		ft_putendl_fd(" »", 2);
		return (1);
	}
	return (0);
}

int	ft_split_char_separator(
	t_data_split **data, t_args_list **args_list, char *input, char separator)
{
	ft_printf("%c++\n", input[(*data)->i]);
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
	ft_printf("%c--\n", input[(*data)->i]);
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->space = 1;
	(*data)->start = (*data)->i;
	return (1);
}

int	ft_split_string_separator(
	t_data_split **data, t_args_list **args_list, char *input, char *separator)
{
	ft_printf("%c++\n", input[(*data)->i]);
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
	ft_printf("%c--\n", input[(*data)->i]);
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->space = 1;
	(*data)->start = (*data)->i;
	return (1);
}
