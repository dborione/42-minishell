/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:08:23 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	y;
	size_t	little_len;
	char	*pb;

	i = 0;
	pb = (char *)big;
	little_len = ft_strlen(little);
	if (little_len == 0 || big == little)
		return ((char *)big);
	while (i < len && pb[i])
	{
		y = 0;
		while (pb[i + y] && little[y] && pb[i + y] == little[y] && i + y < len)
			y++;
		if (y == little_len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int     main(void)
{
        char    *big = "abc\0";
        char    *little = "abcdef\0";
		size_t	n = 5;

        printf("real '%p'\n", strnstr(big, little, n));
        printf("fake '%p'\n", ft_strnstr(big, little, n));
		
		//printf("'%s'\n", ft_strnstr(, "dolor", -1));
        return (0);
}*/
