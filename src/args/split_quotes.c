/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:33:43 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 13:48:46 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
char	*ft_let_include_var(t_data_split *data, char *tmp)
{
	char	*var_tmp;
	char	*res;

	var_tmp = ft_include_var(data, tmp);
	if (!var_tmp)
		return (NULL);
	res = ft_strjoin(data->tmp, var_tmp);
	free(var_tmp);
	return (res);
}

size_t	ft_split_from_quotes(
	t_data_split *data, t_args_list **cmd_split, char *input)
{
	char	*tmp;
	char	*res;
	size_t	len;

	tmp = ft_between_quotes(&input[data->i]);
	if (!tmp)
		return (0);
	len = ft_strlen(tmp);
	if (input[data->i] != '\'')
		res = ft_let_include_var(data, tmp);
	else
		res = ft_strjoin(data->tmp, tmp);
	free(tmp);
	if (!res)
	{
		free(tmp);
		return (0);
	}
	if (!ft_join_args(cmd_split, res))
	{
		free(res);
		return (0);
	}
	free(res);
	return (len + 2);
}
