/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:32:26 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 12:24:13 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
char	*ft_include_vars_between_quotes(
	t_data_split *data, char *str_before, char *tmp)
{
	char	**var_tmp_after;
	char	**var_tmp_before;
	char	*res;

	var_tmp_after = ft_include_var(data, tmp, 1);
	if (!var_tmp_after)
	{
		free(tmp);
		return (0);
	}
	var_tmp_before = ft_include_var(data, str_before, 1);
	if (!var_tmp_after)
	{
		free(tmp);
		ft_free_split(var_tmp_after);
		return (0);
	}
	res = ft_strjoin(var_tmp_before[0], var_tmp_after[0]);
	ft_free_split(var_tmp_after);
	ft_free_split(var_tmp_before);
	return (res);
}

static
int	ft_add_and_free(t_args_list **cmd_split, char *res)
{
	if (!ft_add_arg_to_list(cmd_split, res))
	{
		free(res);
		return (0);
	}
	free(res);
	return (1);
}

size_t	ft_join_from_quotes(
	t_data_split *data, t_args_list **cmd_split,
	char *str_before, char *str_after)
{
	char	*tmp;
	char	*res;
	size_t	len;

	tmp = ft_between_quotes(str_after);
	if (!tmp)
		return (0);
	len = ft_strlen(tmp);
	if (str_after[0] != '\'')
	{
		res = ft_include_vars_between_quotes(data, str_before, tmp);
		if (!res)
			return (0);
	}
	else
		res = ft_strjoin(str_before, tmp);
	free(tmp);
	if (!res)
		return (0);
	if (!ft_add_and_free(cmd_split, res))
		return (0);
	return (len + 2);
}
