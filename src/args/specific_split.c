/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specific_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:43:39 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 18:46:06 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_space_join(
	t_data_split **data, t_args_list **args_list, char **var_tmp, char *input)
{
	if (!ft_join_args(args_list, var_tmp[0]))
	{
		ft_free_split(var_tmp);
		return (0);
	}
	(*data)->tmp[0] = '\0';
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->start = (*data)->i;
	(*data)->space = 1;
	return (1);
}

int	ft_space_split(t_data_split **data, t_args_list **args_list, char *input)
{
	char	**var_tmp;

	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	if ((*data)->space)
		var_tmp = ft_include_var(*data, (*data)->tmp, 0);
	else
		var_tmp = ft_include_var(*data, (*data)->tmp, 1);
	if (!var_tmp)
		return (0);
	if (!(*data)->space)
	{
		if (!ft_space_join(data, args_list, var_tmp, input))
			return (0);
	}
	else if (!ft_one_split(data, args_list, input, var_tmp[0]))
	{
		ft_free_split(var_tmp);
		return (0);
	}
	(*data)->space = 1;
	return (ft_include_var_split(args_list, var_tmp));
}

int	ft_quotes_split(t_data_split **data, t_args_list **args_list, char *input)
{
	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	if (!(*data)->space)
		(*data)->start = ft_split_from_quotes(*data, args_list, input);
	else
	{
		(*data)->start = ft_join_from_quotes(
				*data, args_list, (*data)->tmp, &input[(*data)->i]);
	}
	if (!(*data)->start)
	{
		ft_exit_split_args(data, args_list);
		return (0);
	}
	(*data)->i += (*data)->start;
	if (!ft_isspace(input[(*data)->i]))
		(*data)->space = 0;
	else
		(*data)->space = 1;
	while (ft_isspace(input[(*data)->i]))
		(*data)->i++;
	(*data)->start = (*data)->i;
	(*data)->tmp[0] = '\0';
	return (1);
}

static
int	ft_last_error(t_args_list **args_list, char **var_tmp)
{
	ft_free_args_list(args_list);
	ft_free_split(var_tmp);
	*args_list = NULL;
	return (0);
}

int	ft_last_arg(t_data_split *data, t_args_list **args_list)
{
	char	**var_tmp;

	if (data->space)
		var_tmp = ft_include_var(data, data->tmp, 0);
	else
		var_tmp = ft_include_var(data, data->tmp, 1);
	if (!var_tmp)
		return (0);
	if (!data->space)
	{
		if (!ft_join_args(args_list, var_tmp[0]))
			return (ft_last_error(args_list, var_tmp));
	}
	else if (!ft_add_arg_to_list(args_list, var_tmp[0]))
		return (ft_last_error(args_list, var_tmp));
	return (ft_include_var_split(args_list, var_tmp));
}
