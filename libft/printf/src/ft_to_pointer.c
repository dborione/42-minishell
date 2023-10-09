/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:25:01 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/01/11 16:25:09 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_ptrlen(size_t number)
{
	int	len;

	if (!number)
		return (1);
	len = 0;
	while (number)
	{
		number = number / 16;
		len++;
	}
	return (len);
}

char	*ft_to_pointer(size_t number)
{
	char	*hexstr;
	char	*base;
	int		len;
	int		i;

	len = ft_ptrlen(number);
	hexstr = malloc(sizeof(char) * (len + 1));
	if (!hexstr)
		return (NULL);
	base = ft_betterdup("0123456789abcdef", 16);
	if (!base)
	{
		free(hexstr);
		return (NULL);
	}
	hexstr[len] = '\0';
	i = len - 1;
	hexstr[0] = '0';
	while (number && i >= 0)
	{
		hexstr[i--] = base[number % 16];
		number /= 16;
	}
	free(base);
	return (hexstr);
}
