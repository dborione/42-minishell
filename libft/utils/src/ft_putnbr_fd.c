/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:57:04 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

static void	ft_putpos_fd(int nb, int fd)

{
	char	ascii;

	if (nb > 9)
	{
		ft_putpos_fd(nb / 10, fd);
	}
	ascii = nb % 10 + 48;
	ft_putchar_fd(ascii, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
			ft_putstr_fd("2147483648", fd);
		else
			ft_putpos_fd(n *= -1, fd);
	}
	else
		ft_putpos_fd(n, fd);
}
/*
int	main()
{
	ft_putnbr_fd(-2147483648, 1);
	return (0);
}
*/
