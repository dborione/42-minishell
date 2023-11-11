/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:50:32 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/11 01:08:39 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_print_char(char c, int *len)
{
	int	res;

	res = 0;
	if (!c)
		return (0);
	res = ft_putchar_prf(c);
	if (res == -1)
		*len = -1;
	else
		*len += 1;
	return (res);
}

int	ft_print_arg(t_list *args, char type, int *count)
{
	char	*p;
	int		p_count;

	p = (char *) args->content;
	p_count = 0;
	if (!p)
		return (-1);
	if (type == 'c' && (p[0] == '\0'))
		p_count = ft_putchar_prf(p[0]);
	else
		p_count = ft_putstr_prf(p);
	if (p_count == -1)
		return (-1);
	*count += p_count;
	return (*count);
}

static char	*ft_get_str(char *str)
{
	if (!str)
		return (ft_betterdup("(null)", 6));
	return (ft_strdup(str));
}

static char	*ft_get_ptr(size_t n)

{
	char	*hex;
	char	*res;

	hex = ft_to_pointer(n);
	if (!hex)
		return (NULL);
	res = ft_strjoin("0x", hex);
	free(hex);
	if (!res)
		return (NULL);
	return (res);
}

void	*ft_set_arg(va_list *args, char arg_t)
{
	void	*arg;

	if (arg_t == '%')
		arg = ft_ptrchar('%');
	else if (arg_t == 'i')
		arg = ft_itoa(va_arg(*args, int));
	else if (arg_t == 'u')
		arg = ft_u_itoa(va_arg(*args, int));
	else if (arg_t == 'd')
		arg = ft_itoa(va_arg(*args, int));
	else if (arg_t == 'c')
		arg = ft_ptrchar(va_arg(*args, int));
	else if (arg_t == 's')
		arg = ft_get_str(va_arg(*args, char *));
	else if (arg_t == 'p')
		arg = ft_get_ptr(va_arg(*args, size_t));
	else if (arg_t == 'x')
		arg = ft_num_to_hex(va_arg(*args, unsigned int), 0);
	else
		arg = ft_num_to_hex(va_arg(*args, unsigned int), 1);
	if (!arg)
		return (NULL);
	return (arg);
}
