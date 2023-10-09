/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:55:12 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (dst && dst[len] && len < dstsize)
		len++;
	while (src[i] && len + i + 1 < dstsize)
	{
			dst[len + i] = src[i];
		i++;
	}
	if (len < dstsize)
		dst[len + i] = '\0';
	while (src[i])
		i++;
	return (len + i);
}
/*
#include <stdio.h>

int	main(void)
{

	char	*src = "the cake is a lie !\0I'm hidden lol\r\n";
	char	dst[256] = "abcd";
	char	dst2[256] = "abcd";
	size_t	max = 0;//ft_strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4;

	//printf("fake %lu, %s\n", ft_strlcat(dst, src, max), dst);
	printf("fake %lu, %s\n", ft_strlcat(((void *)0), src, max), dst);
	//printf("real %lu, %s\n", strlcat(dst2, src, max), dst2);
	printf("real %lu, %s\n", strlcat(((void *)0), src, max), dst2);
	return (0);
}
*/
