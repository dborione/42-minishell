/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:53:38 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dp;
	char	*sp;

	i = 0;
	dp = dst;
	sp = (char *)src;
	if (!src && !dst)
		return (NULL);
	while (i < n)
	{
		*dp++ = *sp++;
		i++;
	}
	return (dst);
}
/*
#include <stdio.h>

int	main(void)
{
	void	*dst = NULL;
	void	*src = NULL;

	printf("fake %s, %s\n", ft_memcpy(&dst, &src, 0), dst);
	printf("fake %s\n", ft_memcpy(NULL, NULL, 1));

	void	*dst2 = NULL;
	void	*src2 = NULL;

	printf("real %s, %s\n", memcpy(&dst2, &src2, 0), dst2);
	printf("real %s\n", memcpy(NULL, NULL, 1));
	return (0);
}
*/
