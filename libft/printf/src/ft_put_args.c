/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:21:33 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/02/01 11:37:05 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putchar_prf(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_prf(char *str)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	while (str[i])
	{
		if (done == -1)
			return (-1);
		done = ft_putchar_prf(str[i]);
		i++;
	}
	if (done == -1)
		return (-1);
	return (i);
}
