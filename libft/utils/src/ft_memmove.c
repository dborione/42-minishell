/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:06:33 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dp;
	unsigned char	*sp;

	i = 0;
	dp = (unsigned char *)dst;
	sp = (unsigned char *)src;
	if (!src && !dst)
		return (NULL);
	if (dp > sp)
	{
		while (++i <= len)
			dp[len - i] = sp[len - i];
	}
	else
	{
		while (i < len)
		{
			*(dp++) = *(sp++);
			i++;
		}
	}
	return (dst);
}
/*
int	main(void)
{
	char	src2[6] = "abcde\0";
	
	ft_putstr_fd("real : \n", 1);
	ft_putstr_fd(memmove(&src2[1], &src2[0], 5), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(src2, 1);
	ft_putchar_fd('\n', 1);
	
	char	src[6] = "abcde\0";

	ft_putstr_fd("fake : \n", 1);
	ft_putstr_fd(ft_memmove(&src[1], &src[0], 5), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(src, 1);
	ft_putchar_fd('\n', 1);	

	return (0);
}
*/
