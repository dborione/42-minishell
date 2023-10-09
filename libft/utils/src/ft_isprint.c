/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:17:24 by rbarbiot          #+#    #+#             */
/*   Updated: 2022/11/06 15:13:42 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char tests[] = "123abc \t\r\n\0";
	int	i = 0;

	while (tests[i])
	{
		printf("%c : %d\n", tests[i], ft_isprint(tests[i]));
		printf("%c : %d\n\n", tests[i], isprint(tests[i]));
		i++;
	}
	return (0);
}
*/
