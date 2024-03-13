/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:32:27 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 15:32:57 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
t_data_include_var	*ft_init_include_var(char *input, int quotes)
{
	t_data_include_var	*data_include;

	data_include = malloc(sizeof(t_data_include_var));
	if (!data_include)
		return (NULL);
	data_include->i = 0;
	data_include->start = 0;
	data_include->res = NULL;
	data_include->len = ft_strlen(input);
	data_include->quotes = quotes;
	return (data_include);
}

static
int	ft_include_loop(
	t_data_split *data, char *input, t_data_include_var **data_i)
{
	if (input[(*data_i)->i] == '$'
		&& (ft_is_var_char(input[(*data_i)->i + 1]) 
			|| input[(*data_i)->i + 1] == '?'))
	{
		if (!ft_include_envp_var(data, input, data_i))
			return (0);
	}
	else if (!(*data_i)->quotes && (*data_i)->len < 3
		&& input[(*data_i)->i] == '~'
		&& (!input[(*data_i)->i + 1]
			|| ft_isspace(input[(*data_i)->i + 1])
			|| input[(*data_i)->i + 1] == '/'))
	{
		if (!ft_include_home(data, input, data_i))
			return (0);
	}
	else
		(*data_i)->i++;
	return (1);
}

static
char	**ft_include_split(char *input, int no_split)
{
	char	**res;

	if (no_split)
	{
		res = malloc(sizeof(char *) * 2);
		if (!res)
			return (NULL);
		res[0] = ft_strdup(input);
		if (!res[0])
		{
			free(res);
			return (NULL);
		}
		res[1] = NULL;
		return (res);
	}
	return (ft_split(input, ' '));
}

static
char	**ft_include_res(t_data_include_var **data_i, char *input)
{
	char	**res;

	if ((*data_i)->start && input[(*data_i)->start])
	{
		(*data_i)->res = ft_var_join(
				(*data_i)->res, &input[(*data_i)->start],
				ft_strlen(&input[(*data_i)->start]));
		if (!(*data_i)->res)
		{
			free(*data_i);
			return (NULL);
		}
	}
	if ((*data_i)->res)
	{
		res = ft_include_split((*data_i)->res, (*data_i)->quotes);
		free((*data_i)->res);
		free(*data_i);
		return (res);
	}
	free(*data_i);
	return (ft_include_split(input, 1));
}

char	**ft_include_var(t_data_split *data, char *input, int quotes)
{
	t_data_include_var	*data_i;

	data_i = ft_init_include_var(input, quotes);
	if (!data_i)
		return (NULL);
	while (input[data_i->i])
	{
		if (!ft_include_loop(data, input, &data_i))
		{
			if (data_i->res)
				free(data_i->res);
			free(data_i);
			return (NULL);
		}
	}
	return (ft_include_res(&data_i, input));
}
