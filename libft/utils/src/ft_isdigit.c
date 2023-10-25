/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:22:42 by rbarbiot          #+#    #+#             */
/*   Updated: 2022/10/04 17:29:54 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	tests[] = "123abc\0";
	int		i = 0;
	
	while (tests[i])
	{
		printf("%c : %d\n", tests[i], ft_isdigit(tests[i]));
		i++;
	}
	return (0);
}
*/
