/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_separators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:16:55 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 12:13:10 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_set_type_separator(t_args_list **args_list)
{
	t_args_list	*target_arg;

	target_arg = *args_list;
	while (target_arg->next)
		target_arg = target_arg->next;
	target_arg->separator = 1;
}

static
int	ft_set_previous_arg(
	t_data_split **data, t_args_list **args_list, char *input)
{
	char	**tmp;

	tmp = ft_include_var(*data, (*data)->tmp, 0);
	if (!tmp)
		return (0);
	if (!(*data)->space && (*data)->tmp[0])
	{
		if (!ft_join_args(args_list, tmp[0]))
		{
			ft_free_split(tmp);
			return (0);
		}
		(*data)->tmp[0] = '\0';
	}
	else if ((*data)->tmp[0]
		&& !ft_one_split(data, args_list, input, tmp[0]) && (*data)->tmp[0])
	{
		ft_free_split(tmp);
		return (0);
	}
	return (ft_include_var_split(args_list, tmp));
}

int	ft_split_char_separator(
	t_data_split **data, t_args_list **args_list, char *input, char separator)
{
	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	if (!ft_set_previous_arg(data, args_list, input))
		return (0);
	(*data)->tmp[0] = separator;
	(*data)->tmp[1] = '\0';
	if (!ft_one_split(data, args_list, input, (*data)->tmp))
		return (0);
	ft_set_type_separator(args_list);
	(*data)->i++;
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->space = 1;
	(*data)->start = (*data)->i;
	(*data)->tmp[0] = '\0';
	return (1);
}

int	ft_split_string_separator(
	t_data_split **data, t_args_list **args_list, char *input, char *separator)
{
	if (!ft_set_previous_arg(data, args_list, input))
		return (0);
	(*data)->tmp[0] = separator[0];
	(*data)->tmp[1] = separator[1];
	(*data)->tmp[2] = '\0';
	if (!ft_one_split(data, args_list, input, (*data)->tmp))
		return (0);
	ft_set_type_separator(args_list);
	(*data)->i += 2;
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->space = 1;
	(*data)->start = (*data)->i;
	(*data)->tmp[0] = '\0';
	return (1);
}
