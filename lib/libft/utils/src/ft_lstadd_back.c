/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:32:37 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:25:52 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*target;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		target = ft_lstlast(*lst);
		target->next = new;
	}
}
/*
int	main(void)
{
	ft_lstadd_back(NULL, NULL);
	return (0);
}
*/
