/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:48:49 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 13:34:13 by rbarbiot         ###   ########.fr       */
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

int	ft_has_endof_quotes(char *input, char quote)
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

