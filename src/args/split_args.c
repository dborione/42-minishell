/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:14:26 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/30 13:20:11 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char		**ft_split_args(char *input)
{
	char		**res;
	size_t		len;
	t_args_list	*args_list;

	len = ft_strlen(input);
	if (!ft_memchr(input, '"', len) && !ft_memchr(input, '\'', len))
		return (ft_split(input, ' '));
	args_list = ft_input_to_args_list(input, len);
	res = ft_args_list_to_str_split(&args_list);
	ft_free_args_list(&args_list);
	if (!res)
		return (NULL);
	return (res);
}
