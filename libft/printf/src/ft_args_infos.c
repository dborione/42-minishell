/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:59:08 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/01/30 18:27:13 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_is_type(char c)
{
	return (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X');
}

static int	ft_count_args(const char *input, size_t len)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (i > 0 && input[i] == '%' && input[i - 1] == '%')
			i++;
		else if ((i > 0 && i < len)
			&& input[i - 1] == '%' && ft_is_type(input[i]))
			count++;
		i++;
	}
	return (count);
}

char	*ft_gettypes(const char *input, size_t len)
{
	size_t	i;
	size_t	y;
	char	*types_list;

	if (!ft_init_gettype(input, &i, &y))
		return (NULL);
	types_list = malloc(sizeof(char) * (ft_count_args(input, len) + 1));
	if (!types_list)
		return (NULL);
	while (i < len)
	{
		if (i > 0 && input[i] == '%' && input[i - 1] == '%')
			i++;
		else if ((i > 0 && i < len)
			&& input[i - 1] == '%' && ft_is_type(input[i]))
		{
			types_list[y] = input[i];
			y++;
		}
		i++;
	}
	types_list[y] = '\0';
	return (types_list);
}

char	*ft_ptrchar(int c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_list	*ft_get_args(va_list args, char arg_t)
{
	t_list	*tmp;
	void	*arg;

	tmp = ft_lstnew(NULL);
	if (!tmp)
		return (NULL);
	arg = ft_set_arg(args, arg_t);
	if (!arg)
	{
		ft_lstdelone(tmp, free);
		return (NULL);
	}
	tmp->content = arg;
	return (tmp);
}
