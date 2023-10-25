/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 22:20:20 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/02 22:00:04 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "./utils/libft_utils.h"

int		ft_printf(const char *input, ...);
char	*get_next_line(int fd);
char	*get_next_line_ml_fd(int fd);
#endif