/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:22:02 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*target;

	if (lst)
	{
		while (*lst)
		{
			target = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = target;
		}
		*lst = NULL;
	}
}
/*
int	main(void)
{
	t_list *test = ft_lstnew("test");

	ft_lstclear(&test, NULL);
	return (0);
}
*/
