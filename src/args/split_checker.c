/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 08:56:51 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 17:14:24 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_try_split(t_data_split **data,
	t_args_list **args_list, char *input)
{
	int	res;

	res = 1;
	if (ft_is_speparators(&input[(*data)->i]))
	{
		res = ft_split_string_separator(
				data, args_list, input, &input[(*data)->i]);
	}
	else if (input[(*data)->i] == '<' || input[(*data)->i] == '|'
		|| input[(*data)->i] == '>')
	{
		res = ft_split_char_separator(
				data, args_list, input, input[(*data)->i]);
	}
	else if (ft_isspace(input[(*data)->i]))
		res = ft_space_split(data, args_list, input);
	else if ((input[(*data)->i] == '\'' || input[(*data)->i] == '"')
		&& ft_has_endof_quotes(&input[(*data)->i], input[(*data)->i]))
		res = ft_quotes_split(data, args_list, input);
	else
		return (0);
	if (!res)
		return (-1);
	return (res);
}

int	ft_split_checker(
	t_shell_data **shell_data, t_data_split **data,
	t_args_list **args_list, char *input)
{
	int	res;

	if (ft_is_invalid_args_separator(shell_data, &input[(*data)->i]))
	{
		ft_free_args_list(args_list);
		free((*data)->tmp);
		free(*data);
		return (0);
	}
	res = ft_try_split(data, args_list, input);
	if (res == -1)
		return (0);
	if (res)
		return (res);
	(*data)->tmp[(*data)->i - (*data)->start] = input[(*data)->i];
	(*data)->i++;
	return (1);
}
