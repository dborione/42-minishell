/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:05:44 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = n;
	p = (unsigned char *)s;
	while (i > 0)
	{
		if (*p == (unsigned char)c)
			return ((void *)s + (n - i));
		++p;
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s = "goya\0";
	char	c = 'g';

	printf("'%p'\n", ft_memchr(s, c, 10));
	printf("'%p'\n", memchr(s, c, 10));
	return (0);
}
*/
