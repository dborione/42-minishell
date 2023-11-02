/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:48:49 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 01:48:13 by rbarbiot         ###   ########.fr       */
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
		//ft_putchar_fd(res[i - 1], 1);
		i++;
	}
	//ft_putchar_fd('\n', 1);
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

size_t	ft_split_from_quotes(t_data_split *data, t_args_list **cmd_split, char *input)//, char *str_before, char *str_after)
{
	char	*tmp;
	//char	*tmp2;
	size_t	len;
	//size_t	i;

	tmp = ft_between_quotes(&input[data->i]);
	//ft_printf("res btw q |%s|\n", tmp);
	if (!tmp)
		return (0);
	len = ft_strlen(tmp);
	// i = 0;
	// while (input[data->i + i] && i < (len + 2))
	// 	i++;
	// if (i == (len + 2) )
	// {
	// 	if ((input[data->i + i] == '\'' || input[data->i + i] == '"')
	// 		&& ft_has_endof_quotes(&input[data->i + i], input[data->i + i]))
	// 	{
			
	// 	}
	// }

	if (!ft_join_args(cmd_split, tmp))
	{
		free(tmp);
		return (0);
	}

	// if (!ft_add_arg_to_list(cmd_split, tmp))
	// {
	// 	free(tmp);
	// 	return (0);
	// }

	free(tmp);
	// data->space = 1;
	// data->i += data->start;
	// while (ft_isspace(input[data->i]))
	// 	data->i++;
	// data->start = data->i;
	return (len + 2);
}
