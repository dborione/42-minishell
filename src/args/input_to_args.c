/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:15:02 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 02:08:03 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
size_t	ft_join_from_quotes(t_args_list **cmd_split, char *str_before, char *str_after)
{
	char	*tmp;
	char	*res;
	size_t	len;

	tmp = ft_between_quotes(str_after);
	if (!tmp)
		return (0);
	res = ft_strjoin(str_before, tmp);
	if (!res)
	{
		free(tmp);
		return (0);
	}
	if (!ft_add_arg_to_list(cmd_split, res))
	{
		free(tmp);
		return (0);
	}
	len = ft_strlen(tmp);
	free(tmp);
	return (len + 2);
}

static
int			ft_split_from_space(t_data_split **data, t_args_list **args_list, char *input)
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

static
int			ft_init_data_split(t_data_split **data, t_args_list **args_list, size_t len)
{
	*data = malloc(sizeof(t_data_split));
	if (!(*data))
		return (0);
	*args_list = NULL;
	(*data)->tmp = malloc(sizeof(char) * (len + 1));
	if (!(*data)->tmp)
	{
		free(data);
		return (0);
	}
	(*data)->i = 0;
	(*data)->space = 1;
	return (1);
}

static
void		ft_finish_split_args(t_data_split **data, t_args_list **args_list)
{
	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	if ((*data)->tmp[0])
	{
		if (!(*data)->space)
		{
			if (!ft_join_args(args_list, (*data)->tmp))
			{
				ft_free_args_list(args_list);
				*args_list = NULL;
			}
		}
		else if (!ft_add_arg_to_list(args_list, (*data)->tmp))
		{
			ft_free_args_list(args_list);
			*args_list = NULL;
		}
	}
	free((*data)->tmp);
	free(*data);
}

t_args_list	*ft_input_to_args_list(char *input, size_t len)
{
	t_data_split	*data;
	t_args_list	*args_list;

	if (!ft_init_data_split(&data, &args_list, len))
		return (NULL);
	while (ft_isspace(input[data->i]))
			data->i++;
	data->start = data->i;
	while (input[data->i])
	{
		if (ft_isspace(input[data->i]))
		{
			data->tmp[data->i - data->start] = '\0';
			if (!data->space)
			{
				if (!ft_join_args(&args_list, data->tmp))
					return (NULL);
			}
			else if (!ft_split_from_space(&data, &args_list, input))
				return (NULL);
			data->space = 1;
		}
		else if ((input[data->i] == '\'' || input[data->i] == '"') && ft_has_endof_quotes(&input[data->i], input[data->i]))
		{
			data->tmp[data->i - data->start] = '\0';
			if (!data->space) // retirer la verif de l'espace
				data->start = ft_split_from_quotes(data, &args_list, input);
			else
				data->start = ft_join_from_quotes(&args_list, data->tmp, &input[data->i]);
			if (!data->start)
				return (ft_exit_split_args(&data, &args_list));
			data->i += data->start;
			if (!ft_isspace(input[data->i]))
				data->space = 0;
			while (ft_isspace(input[data->i]))
				data->i++;
			data->start = data->i;
			data->tmp[0] = '\0';
		}
		else
		{
			data->tmp[data->i - data->start] = input[data->i];
			data->i++;
		}
	}
	ft_finish_split_args(&data, &args_list);
	return (args_list);
}
