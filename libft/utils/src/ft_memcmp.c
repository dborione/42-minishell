/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:49:24 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (n == 0)
		return (0);
	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while ((p1[i] == p2[i]) && i + 1 < n)
		i++;
	return (p1[i] - p2[i]);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*s1 = "zyxbcdefgh";
	char	*s2 = "abcdefgxyz";
	size_t	n = 0;

	printf("real : %d\n", memcmp(s1, s2, n));
	printf("fake : %d\n", ft_memcmp(s1, s2, n));
	return (0);
}*/
