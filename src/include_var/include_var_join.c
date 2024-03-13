/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_var_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:56 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 14:17:00 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
char	*ft_new_include(char *str, size_t len)
{
	char	*res;
	size_t	i;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_var_join(char *s1, char *s2, size_t len)
{
	int		i;
	int		y;
	char	*res;

	if (!s1 && (!s2 || !s2[0]))
		return (NULL);
	if (!s1)
		return (ft_new_include(s2, len));
	i = -1;
	y = -1;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	while (s1[++y])
		res[y] = s1[y];
	while (++i < (int)len && s2 && s2[i])
		res[y + i] = s2[i];
	res[y + i] = '\0';
	free(s1);
	return (res);
}
