/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endswith.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 10:27:35 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 15:41:41 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

int	ft_endswith(const char *str, const char *end)
{
	size_t	strlen;
	size_t	endlen;

	if (!str || !end)
		return (0);
	strlen = ft_strlen(str);
	endlen = ft_strlen(end);
	if (strlen < endlen)
		return (0);
	while (strlen && endlen)
	{
		if (str[--strlen] != end[--endlen])
			return (0);
	}
	return (1);
}
