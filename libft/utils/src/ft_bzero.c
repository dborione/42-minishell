/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:21:31 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*d;

	i = 0;
	d = s;
	while (i < n)
	{
		*d++ = '\0';
		i++;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	void	*test = "111\0";
	unsigned char	*p;
	bzero(&test, 1);
	p = test;

	void	*test2 = "111\0";
	unsigned char	*p2;
	ft_bzero(&test2, 1);
	p2 = test2;

	printf("real %c\n", *p);
	printf("real %c\n", *p++);
	printf("real %s\n", test);
	
	printf("fake %c\n", *p2);
	printf("fake %c\n", *p2++);
	printf("fake %s\n", test2);
	
	return (0);
}
*/
