/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:15:02 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/09 10:47:22 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int			ft_init_data_split(t_shell_data *shell_data, t_data_split **data, t_args_list **args_list, size_t len)
{
	*data = malloc(sizeof(t_data_split));
	if (!(*data))
		return (0);
	(*data)->envp = shell_data->envp;
	(*data)->exit_code = shell_data->exit_code;
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
int		ft_finish_split_args(t_data_split **data, t_args_list **args_list)
{
	char	*var_tmp;

	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	if ((*data)->tmp[0])
	{
		var_tmp = ft_include_var(*data, (*data)->tmp);
		if (!var_tmp)
		{
			free((*data)->tmp);
			free(*data);
			return (0);
		}
		if (!(*data)->space)
		{
			if (!ft_join_args(args_list, var_tmp))
			{
				ft_free_args_list(args_list);
				*args_list = NULL;
			}
		}
		else if (!ft_add_arg_to_list(args_list, var_tmp))
		{
			ft_free_args_list(args_list);
			*args_list = NULL;
		}
	}
	free((*data)->tmp);
	free(*data);
	return (1);
}

t_args_list	*ft_input_to_args_list(t_shell_data **shell_data, char *input, size_t len)
{
	t_data_split	*data;
	t_args_list	*args_list;

	if (!ft_init_data_split(*shell_data, &data, &args_list, len))
		return (NULL);
	while (ft_isspace(input[data->i]))
			data->i++;
	data->start = data->i;
	while (input[data->i])
	{
		// ajouter data->error et check a chaque boucle
		if (ft_is_invalid_args_separator(shell_data, &input[data->i]))
		{
			ft_free_args_list(&args_list);
			return (NULL);
		}
		if (input[data->i] == '<' || input[data->i] == '|' || input[data->i] == '>')
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
	ft_finish_split_args(&data, &args_list); // prendre en charge l'erreur
	return (args_list);
}
