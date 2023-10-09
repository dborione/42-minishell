/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:42:15 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*d;

	i = 0;
	d = b;
	while (i < len)
	{
		*d++ = c;
		i++;
	}
	return (b);
}
/*
#include <stdio.h>

int	main(void)
{
	void	*test = "22\0";
	void	*test2 = "22\0";

	printf("fake : %s, %s\n", ft_memset(&test, 'a', 1), test);
	printf("real : %s, %s\n", memset(&test2, 'a', 1), test2);
	return (0);
}
*/
