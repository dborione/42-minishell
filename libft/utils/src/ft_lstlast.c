/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:23:58 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*target;

	target = lst;
	while (target)
	{
		if (target->next)
			target = target->next;
		else
			return (target);
	}
	return (lst);
}
/*
int	main(void)
{
	ft_lstlast(NULL);
	return (0);
}
*/
