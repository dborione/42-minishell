/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:47:16 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*target;

	if (lst && f)
	{
		target = lst;
		while (target)
		{
			f(target->content);
			target = target->next;
		}
	}	
}
/*
int	main(void)
{
	ft_lstiter(NULL, NULL);
	return (0);
}
*/
