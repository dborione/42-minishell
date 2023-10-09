/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:48:14 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (n == 0)
		return (0);
	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while ((p1[i] && p2[i]) && (p1[i] == p2[i]) && i + 1 < n)
		i++;
	return (p1[i] - p2[i]);
}
/*
#include <stdio.h>

int	main(void)
{
	//char	*s1 = "abc\0";
	//char	*s2 = "abd";
	//size_t	n = 4;

	//printf("real : %d\n", strncmp(s1, s2, n));
	//printf("fake : %d\n", ft_strncmp(s1, s2, n));
	
	printf("'%d'", ft_strncmp("zyxbcdefgh", "abcdwxyz", 0));
	return (0);
}
*/
