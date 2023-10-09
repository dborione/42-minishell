/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isacii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:46:44 by rbarbiot          #+#    #+#             */
/*   Updated: 2022/10/04 18:14:50 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char	tests[] = "123abc:'?à\0";
	int		i = 0;

	while (tests[i])
	{
		printf("fake %c : %d\n", tests[i], ft_isascii(tests[i]));
		printf("real %c : %d\n\n", tests[i], isascii(tests[i]));
		i++;
	}

	return (0);
}
*/
