/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:43:59 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 15:34:01 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
void	ft_skip_var_name(char *input, size_t *i)
{
	if (input[*i] == '?')
		(*i)++;
	else
	{
		while (input[*i] && (ft_is_var_char(input[*i])))
			(*i)++;
	}
}

int	ft_include_envp_var(
	t_data_split *data, char *input, t_data_include_var **data_i)
{
	char		*tmp;

	(*data_i)->res = ft_var_join(
			(*data_i)->res, &input[(*data_i)->start],
			((*data_i)->i)++ - ((*data_i)->start));
	if (!(*data_i)->res)
		return (0);
	(*data_i)->start = (*data_i)->i;
	ft_skip_var_name(input, &(*data_i)->i);
	tmp = ft_get_value(data, &input[(*data_i)->start],
			(*data_i)->i - 1 - ((*data_i)->start - 1));
	if (!tmp)
	{
		free((*data_i)->res);
		return (0);
	}
	(*data_i)->res = ft_var_join((*data_i)->res, tmp, ft_strlen(tmp));
	free(tmp);
	if (!(*data_i)->res)
		return (0);
	(*data_i)->start = (*data_i)->i;
	if (!input[(*data_i)->i])
		(*data_i)->start = 0;
	return (1);
}

int	ft_include_home(
	t_data_split *data, char *input, t_data_include_var **data_i)
{
	(*data_i)->res = ft_var_join(
			(*data_i)->res, &input[(*data_i)->start],
			((*data_i)->i)++ - ((*data_i)->start));
	if (!(*data_i)->res)
		return (0);
	if (input[(*data_i)->i] == '/')
		(*data_i)->i++;
	(*data_i)->start = (*data_i)->i;
	(*data_i)->res = ft_var_join(
			(*data_i)->res, data->home, ft_strlen(data->home));
	return (1);
}
