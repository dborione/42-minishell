/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:15:02 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 15:13:00 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		// ajouter data->error et check a chaque boucle
		if (ft_is_invalid_args_separator(&input[data->i]))
		{
			ft_free_args_list(&args_list);
			return (NULL);
		}
		if (input[data->i] == '<')
			ft_split_char_separator(&data, &args_list, input, input[data->i]);
		else if (input[data->i] == '|')
			ft_split_char_separator(&data, &args_list, input, input[data->i]);
		else if (input[data->i] == '>')
			ft_split_char_separator(&data, &args_list, input, input[data->i]);
		else if (ft_isspace(input[data->i]))
			ft_space_split(&data, &args_list, input);
		else if ((input[data->i] == '\'' || input[data->i] == '"') && ft_has_endof_quotes(&input[data->i], input[data->i]))
			ft_quotes_split(&data, &args_list, input);
		else
		{
			data->tmp[data->i - data->start] = input[data->i];
			data->i++;
		}
	}
	ft_finish_split_args(&data, &args_list);
	return (args_list);
}
