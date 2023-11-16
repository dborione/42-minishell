/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:32:26 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 13:32:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	ft_join_from_quotes(
	t_data_split *data, t_args_list **cmd_split,
	char *str_before, char *str_after)
{
	char	*tmp;
	char	*var_tmp_after;
	char	*var_tmp_before;
	char	*res;
	size_t	len;

	tmp = ft_between_quotes(str_after);
	if (!tmp)
		return (0);
	len = ft_strlen(tmp);
	if (str_after[0] != '\'')
	{
		var_tmp_after = ft_include_var(data, tmp);
		if (!var_tmp_after)
		{
			free(tmp);
			return (0);
		}
		var_tmp_before = ft_include_var(data, str_before);
		if (!var_tmp_after)
		{
			free(var_tmp_after);
			return (0);
		}
		res = ft_strjoin(var_tmp_before, var_tmp_after);
		free(var_tmp_after);
		free(var_tmp_before);
	}
	else
		res = ft_strjoin(str_before, tmp);
	len = ft_strlen(tmp);
	free(tmp);
	if (!res)
		return (0);
	if (!ft_add_arg_to_list(cmd_split, res))
	{
		free(tmp);
		return (0);
	}
	free(res);
	return (len + 2);
}
