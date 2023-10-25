/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startswith.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:22:17 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/09/25 10:27:07 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_utils.h"

int	ft_startswith(const char *str, const char *start)
{
	size_t	i;

	if (!str || !start)
		return (0);
	i = 0;
	while (str[i] && start[i])
	{
		if (str[i] != start[i])
			return (0);
		i++;
	}
	if (start[i])
		return (0);
	return (1);
}
