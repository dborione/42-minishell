/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:15:47 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*target;

	count = 0;
	target = lst;
	while (target)
	{
		target = target->next;
		count++;
	}
	return (count);
}
/*#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_lstsize(NULL));
	return (0);
}
*/
