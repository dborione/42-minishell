/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_itoa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 09:43:39 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/01/09 09:43:45 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static unsigned int	ft_u_intlen(unsigned int n)
{
	unsigned int	new_n;

	if (n > 9)
	{
		new_n = n / 10;
		return (ft_u_intlen(new_n) + 1);
	}
	return (1);
}

char	*ft_u_itoa(unsigned int n)
{
	int		i;
	char	*res;

	i = ft_u_intlen(n);
	res = (char *)malloc(i + 1);
	if (!res)
		return (NULL);
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

char	*ft_betterdup(const char *s, size_t len)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}	
	dup[i] = '\0';
	return (dup);
}
