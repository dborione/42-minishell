/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:33:52 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/01/30 18:23:42 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_percent(const char *str, int *count, size_t *i, int *bol)
{
	int	res;

	res = 0;
	ft_print_char(str[0], &res);
	if (res == -1)
		return (-1);
	*count += res;
	*i += 2;
	*bol = 1;
	return (*count);
}

static int	ft_printf_str(const char *str, t_list *args, size_t len)
{
	size_t	i;
	int		count;
	int		bol;
	t_list	*target;

	bol = 0;
	ft_str_init(&i, &count, &target, args);
	while (count != -1 && i < len)
	{
		while (i < len && (str[i] == '%' && str[i + 1] == '%'))
			if (ft_printf_percent(&str[i], &count, &i, &bol) == -1)
				return (-1);
		if (!bol && str[i] && i > 0 && str[i - 1] == '%' && ft_is_type(str[i]))
		{
			if (ft_print_arg(target, str[i], &count) == -1)
				return (-1);
			target = target->next;
		}
		else if (str[i] && str[i] != '%')
			ft_print_char(str[i], &count);
		i++;
		bol = 0;
	}
	return (count);
}

static int	ft_printf_basic(const char *input, char *args_t, size_t len)
{
	size_t	i;	
	int		count;
	int		done;

	ft_init_basic(&i, &count, &done);
	free(args_t);
	while (i < len)
	{
		if (input[i] != '%')
		{
			done = ft_putchar_prf(input[i]);
			count++;
		}
		else if (input[i + 1] && input[i + 1] == '%')
		{
			done = ft_putchar_prf(input[i]);
			count++;
			i++;
		}
		if (done == -1)
			return (-1);
		i++;
	}
	return (count);
}

int	ft_printf(const char *input, ...)
{
	size_t	i[2];
	va_list	args;
	t_list	*l_args;
	char	*args_t;
	t_list	*tmp;

	if (ft_init_prf(input, &i[0], &i[1], &args_t) == 0)
		return (-1);
	if (args_t[0] == '\0')
		return (ft_printf_basic(input, args_t, i[1]));
	va_start(args, input);
	l_args = ft_get_args(args, args_t[0]);
	if (!l_args)
		return (ft_clear_all(&l_args, args_t, -1));
	while (input[0] && args_t && args_t[i[0]])
	{
		tmp = ft_get_args(args, args_t[i[0]]);
		if (!tmp)
			return (ft_clear_all(&l_args, args_t, -1));
		ft_lstadd_back(&l_args, tmp);
		i[0]++;
	}
	va_end(args);
	i[0] = ft_printf_str(input, l_args, i[1]);
	return (ft_clear_all(&l_args, args_t, i[0]));
}
/*#include <stdio.h>

int		main(void)
{
	if (0)
	{
		char			*test = ft_strdup("LeWeeky");
		int 			i = -2147483648;
		unsigned int	u = 4294967295;

		int real = printf(
			"[ real ] > %%%%, i: %i, p: %p, s: %s, c: %c, u: %u, x: %x, X: %X\n",
			i, &test, test, test[0], u, u, u
		);

		int fake = ft_printf(
			"[ fake ] > %%%%, i: %i, p: %p, s: %s, c: %c, u: %u, x: %x, X: %X\n",
			i, &test, test, test[0], u, u, u
		);

		ft_printf("Real : %d\nFake : %d\n", real, fake);
	}

	if (1)
	{
		int real = printf(
			"Ap!N%i7dTu&9%x\tPB9\n*%iNT~gN%un$o nIALI1%cif(@%%%%%u%i,T9Y_+^IM!%coVF",
			1672703219, 1058157282, -1074037902, 253811685, -1519521731,
			-486075269, -577451743, 1905544618
		);
		printf("\n.\n");
		int fake = ft_printf(
			"Ap!N%i7dTu&9%x\tPB9\n*%iNT~gN%un$o nIALI1%cif(@%%%%%u%i,T9Y_+^IM!%coVF",
			1672703219, 1058157282, -1074037902, 253811685, -1519521731,
			-486075269, -577451743, 1905544618
		);

		printf("\nReal : %d\nFake : %d", real, fake);
	}
	return (0);
}*/
