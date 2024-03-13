/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:33:43 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 17:25:18 by dborione         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
int	ft_append_after(t_args_list **cmd_split, char *str, char **strs)
{
	char	*res;

	res = ft_strjoin(str, strs[0]);
	if (!res)
	{
		ft_free_split(strs);
		return (0);
	}
	if (!ft_join_args(cmd_split, res))
	{
		free(res);
		ft_free_split(strs);
		return (0);
	}
	free(res);
	ft_include_var_split(cmd_split, strs);
	return (1);
}

static
char	**ft_format_after_quotes(t_data_split *data, char *tmp, char quote)
{
	char	**res;

	if (quote != '\'')
		res = ft_include_var(data, tmp, 1);
	else
	{
		res = malloc(sizeof(char *) * (2));
		if (!res)
			return (NULL);
		res[0] = ft_strdup(tmp);
		if (!res[0])
		{
			ft_free_split(res);
			return (NULL);
		}
		res[1] = NULL;
	}
	return (res);
}

static
int	ft_append_before(t_args_list **cmd_split, 
		char **str_before, char **str_after)
{
	if (!ft_join_args(cmd_split, str_before[0]))
	{
		ft_free_split(str_before);
		ft_free_split(str_after);
		return (0);
	}
	if (!ft_include_var_split(cmd_split, str_before))
	{
		ft_free_split(str_after);
		return (0);
	}
	ft_free_split(str_before);
	return (ft_append_after(cmd_split, NULL, str_after));
}

static
int	ft_let_include_var(t_data_split *data, 
		t_args_list **cmd_split, char *tmp, char quote)
{
	char	**var_before_quotes;
	char	**var_after_quotes;

	var_before_quotes = ft_include_var(data, data->tmp, 0);
	if (!var_before_quotes)
		return (0);
	var_after_quotes = ft_format_after_quotes(data, tmp, quote);
	if (!var_after_quotes)
	{
		ft_free_split(var_before_quotes);
		return (0);
	}
	if (var_before_quotes[0] && !var_before_quotes[1])
	{
		ft_append_after(cmd_split, var_before_quotes[0], var_after_quotes);
		ft_free_split(var_before_quotes);
	}
	else
		return (ft_append_before(cmd_split, 
				var_before_quotes, var_after_quotes));
	return (1);
}

size_t	ft_split_from_quotes(
	t_data_split *data, t_args_list **cmd_split, char *input)
{
	char	*tmp;
	int		res;
	size_t	len;

	tmp = ft_between_quotes(&input[data->i]);
	if (!tmp)
		return (0);
	len = ft_strlen(tmp);
	res = ft_let_include_var(data, cmd_split, tmp, input[data->i]);
	free(tmp);
	if (!res)
		return (0);
	return (len + 2);
}
