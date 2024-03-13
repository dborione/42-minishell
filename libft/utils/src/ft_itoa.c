/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:52:10 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 13:34:55 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

static int	ft_intlen(int n)
{
	int	sign;
	int	new_n;

	sign = 0;
	if (n < 0)
		sign = 1;
	if (n == 0)
		return (1);
	if (n > 9 || n < -9)
	{
		new_n = n / 10;
		if (n < 0)
			new_n *= -1;
		return (ft_intlen(new_n) + 1 + sign);
	}
	return (1 + sign);
}

static char	*ft_strset(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*res;

	i = ft_intlen(n);
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	if (n == -2147483648)
		return (ft_strset(res, "-2147483648"));
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
	}
	res[i] = '\0';
	i--;
	while (n > 9)
	{
		res[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	res[i] = n + '0';
	return (res);
}
/*
int	main(void)
{
	int	n = -2147483648;

	printf("%s\n", ft_itoa(n));
	return (0);
}
*/
