/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:27:15 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	ft_memset((unsigned char *)res, 0, nmemb * size);
	return (res);
}
/*
#include <stdio.h>

int	main(void)
{
	int	size = 8539;
	void	*d1;
	void	*d2;

	d1 = ft_calloc(size, sizeof(int));
	d2 = ft_calloc(size, sizeof(int));

	printf("d1: '%c'\n", (char *)d1[0] + '0');
	printf("d2: '%c'\n", (char *)d2[0] + '0');
	return (0);
}
*/
