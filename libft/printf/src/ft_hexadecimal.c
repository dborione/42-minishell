/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 09:33:36 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/01/09 09:34:16 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_hexlen(unsigned int number)
{
	int	len;

	if (!number)
		return (3);
	len = 0;
	while (number)
	{
		number = number / 16;
		len++;
	}
	return (len);
}

static char	*ft_hexformater(unsigned int number, char *base)
{
	char	*hexstr;
	int		len;
	int		i;

	if (number == 0)
		return (ft_betterdup("0", 1));
	len = ft_hexlen(number);
	hexstr = malloc(sizeof(char) * (len + 1));
	if (!hexstr)
		return (NULL);
	hexstr[len] = '\0';
	i = len - 1;
	while (number)
	{
		hexstr[i--] = base[number % 16];
		number /= 16;
	}
	return (hexstr);
}

char	*ft_num_to_hex(unsigned int number, int upper)
{
	char	*res;
	char	*base;

	if (upper)
		base = ft_betterdup("0123456789ABCDEF", 16);
	else
		base = ft_betterdup("0123456789abcdef", 16);
	if (!base)
		return (NULL);
	res = ft_hexformater(number, base);
	free(base);
	if (!res)
		return (NULL);
	return (res);
}
