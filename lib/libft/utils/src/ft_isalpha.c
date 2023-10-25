/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:57:04 by rbarbiot          #+#    #+#             */
/*   Updated: 2022/11/06 15:09:34 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char tests[] = "123abc\0";
	int	i = 0;

	while (tests[i])
	{
		printf("%c : %d\n", tests[i], ft_isalpha(tests[i]));
		i++;
	}
	return (0);
}
*/
