/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:23:21 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/04/14 22:23:38 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../utils/libft_utils.h"
# include <stdarg.h>

int		ft_printf(const char *input, ...);
int		ft_is_type(char c);
char	*ft_gettypes(const char *input, size_t len);
char	*ft_num_to_hex(unsigned int number, int upper);
char	*ft_ptrchar(int c);
char	*ft_u_itoa(unsigned int n);
char	*ft_betterdup(const char *s, size_t len);
char	*ft_to_pointer(size_t number);
int		ft_clear_all(t_list **l_args, char *args_t, int len);
t_list	*ft_get_args(va_list args, char arg_t);
int		ft_print_char(char c, int *len);
int		ft_print_arg(t_list *args, char type, int *count);
void	*ft_set_arg(va_list args, char arg_t);
int		ft_init_prf(const char *input, size_t *i, size_t *len, char **args_t);
void	ft_str_init(size_t *i, int *count, t_list **target, t_list *args);
int		ft_init_gettype(const char *input, size_t *i, size_t *y);
void	ft_init_basic(size_t *i, int *count, int *done);
int		ft_putstr_prf(char *str);
int		ft_putchar_prf(char c);
#endif
