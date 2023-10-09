/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:28:56 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/01/30 18:37:11 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_str_init(size_t *i, int *count, t_list **target, t_list *args)
{
	*i = 0;
	*count = 0;
	*target = args;
}

int	ft_init_gettype(const char *input, size_t *i, size_t *y)
{
	if (!input)
		return (0);
	*i = 0;
	*y = 0;
	return (1);
}

void	ft_init_basic(size_t *i, int *count, int *done)
{
	*i = 0;
	*count = 0;
	*done = 0;
}

int	ft_init_prf(const char *input, size_t *i, size_t *len, char **args_t)
{
	*len = ft_strlen(input);
	*args_t = ft_gettypes(input, *len);
	if (!*args_t)
		return (0);
	*i = 1;
	return (1);
}
