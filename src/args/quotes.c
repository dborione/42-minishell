/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:48:49 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/08 14:56:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
size_t	ft_len_between_quotes(char *str, char quote)
{
	size_t	len;

	len = 0;
	while (str[len + 1] && str[len + 1] != quote)
		len++;
	return (len);
}

char	*ft_between_quotes(char *str)
{
	char	quote;
	size_t	i;
	char	*res;

	quote = str[0];
	i = 1;
	res = malloc(sizeof(char) * (ft_len_between_quotes(str, quote) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == quote)
			break ;
		res[i - 1] = str[i];
		i++;
	}
	res[i - 1] = '\0';
	return (res);
}

int		ft_has_endof_quotes(char *input, char quote)
{
	size_t	i;

	i = 1;
	while (input[i])
	{
		if (input[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_split_from_quotes(t_data_split *data, t_args_list **cmd_split, char *input)
{
	char	*tmp;
	char 	*var_tmp;
	char	*res;
	size_t	len;

	//ft_printf("lets split from quotes\n");
	tmp = ft_between_quotes(&input[data->i]);
	if (!tmp)
		return (0);
	len = ft_strlen(tmp);
	if (input[data->i] != '\'')
	{
		var_tmp = ft_include_var(data, tmp);
		if (!var_tmp)
		{
			free(tmp);
			return (0);
		}
		res = ft_strjoin(data->tmp, var_tmp);
		
	}
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

size_t	ft_join_from_quotes(t_data_split *data, t_args_list **cmd_split, char *str_before, char *str_after)
{
	char	*tmp;
	char 	*var_tmp;
	char	*res;
	size_t	len;

	//ft_printf("lets join\n");
	tmp = ft_between_quotes(str_after);
	if (!tmp)
		return (0);
	len = ft_strlen(tmp);
	if (str_after[0] != '\'')
	{
		var_tmp = ft_include_var(data, tmp);
		if (!var_tmp)
		{
			free(tmp);
			return (0);
		}
		res = ft_strjoin(str_before, var_tmp);
	}
	else
		res = ft_strjoin(str_before, tmp);
	if (!res)
	{
		free(tmp);
		return (0);
	}
	if (!ft_add_arg_to_list(cmd_split, res))
	{
		free(tmp);
		return (0);
	}
	len = ft_strlen(tmp);
	free(tmp);
	return (len + 2);
}
