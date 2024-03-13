/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:29:01 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 15:41:46 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

char	*ft_cleanjoin(char *s1, char *s2)
{
	int		i;
	int		y;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
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
	while (s2 && s2[++i])
		res[y + i] = s2[i];
	res[y + i] = '\0';
	free(s1);
	return (res);
}
