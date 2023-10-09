/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:20:28 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

static char	*ft_str_to_return(char const *s1, char const *s2)
{
	if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else
		return (ft_strdup(""));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	char	*res;

	if (!s1 || !s2)
		return (ft_str_to_return(s1, s2));
	i = 0;
	y = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[y])
	{
		res[y] = s1[y];
		y++;
	}
	while (s2[i])
	{
		res[y + i] = s2[i];
		i++;
	}
	res[y + i] = '\0';
	return (res);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str1 = "Le\0";
	char	*str2 = "Weeky\0";

	printf("%s\n", ft_strjoin(str1, str2));
	printf("%s\n", ft_strjoin(NULL, str2));
	printf("%s\n", ft_strjoin(str1, NULL));
	printf("%s\n", ft_strjoin(NULL, NULL));
	return (0);
}
*/