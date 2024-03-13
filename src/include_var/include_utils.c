/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:46:47 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 15:29:56 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_get_value(t_data_split *data, char *str, size_t end)
{
	char	*tmp;
	char	*res;

	if (str[0] == '?')
		return (ft_itoa(data->exit_code));
	tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	tmp[end] = '\0';
	res = ft_envp_get_value(data->envp, tmp);
	free(tmp);
	return (ft_strdup(res));
}

int	ft_is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
