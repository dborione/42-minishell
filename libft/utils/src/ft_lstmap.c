/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:53:49 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_lst;
	t_list	*n_el;
	t_list	*target;

	if (!lst || !f)
		return (NULL);
	target = lst;
	n_lst = NULL;
	while (target)
	{
		n_el = ft_lstnew(NULL);
		if (!n_el)
		{
			ft_lstclear(&n_lst, del);
			return (NULL);
		}
		n_el->content = f(target->content);
		ft_lstadd_back(&n_lst, n_el);
		target = target->next;
	}
	return (n_lst);
}
/*
#include <stdio.h>

static void	*f_test(void *s)
{
	return (s);
}

static void del_test(void *s)
{
	s = (void *) NULL;
}

int	main(void)
{
	t_list *l = ft_lstnew(" 1 2 3 ");

 	l->next = ft_lstnew("ss");
 	l->next->next = ft_lstnew("-_-");
	
	t_list *res = ft_lstmap(NULL, *f_test, *del_test);
	if (res && res->content)
		printf("'%s'\n", res->content);
	ft_lstclear(&l, *del_test);
	return (0);
}
*/
