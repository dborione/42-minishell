/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:25:29 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/01/23 11:30:31 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_clear_all(t_list **l_args, char *args_t, int len)
{
	if (args_t)
		free(args_t);
	ft_lstclear(l_args, free);
	return (len);
}
