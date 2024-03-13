/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:15:02 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 10:22:41 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
char	*ft_init_tmp(size_t len)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, len);
	return (tmp);
}

static
int	ft_init_data_split(
	t_shell_data *shell_data, t_data_split **data,
	t_args_list **args_list, size_t len)
{
	*data = malloc(sizeof(t_data_split));
	if (!(*data))
		return (0);
	(*data)->envp = shell_data->envp;
	(*data)->exit_code = shell_data->exit_code;
	(*data)->home = ft_envp_get_home(shell_data);
	*args_list = NULL;
	(*data)->tmp = ft_init_tmp(len);
	if (!(*data)->tmp)
	{
		free(data);
		return (0);
	}
	(*data)->tmp[0] = '\0';
	(*data)->i = 0;
	(*data)->space = 1;
	return (1);
}

static
int	ft_finish_split_args(t_data_split **data, t_args_list **args_list)
{
	int		success;

	(*data)->tmp[(*data)->i - (*data)->start] = '\0';
	if ((*data)->tmp[0])
	{
		success = ft_last_arg(*data, args_list);
		if (!success)
		{
			free((*data)->tmp);
			free(*data);
			ft_free_args_list(args_list);
			return (0);
		}
	}
	free((*data)->tmp);
	free(*data);
	return (1);
}

t_args_list	*ft_input_to_args_list(
	t_shell_data **shell_data, char *input, size_t len)
{
	t_data_split	*data;
	t_args_list		*args_list;

	if (!ft_init_data_split(*shell_data, &data, &args_list, len))
		return (NULL);
	while (ft_isspace(input[data->i]))
		data->i++;
	data->start = data->i;
	while (input[data->i])
	{
		if (!ft_split_checker(shell_data, &data, &args_list, input))
			return (NULL);
	}
	if (!ft_finish_split_args(&data, &args_list))
		return (NULL);
	return (args_list);
}
