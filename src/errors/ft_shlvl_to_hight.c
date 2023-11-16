/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl_to_hight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:02:31 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/16 11:55:53 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_shlvl_to_hight(int level)
{
	char	*str_level;
	char	*tmp;

	if (level == 2147483647)
		str_level = ft_strdup("2147483647");
	else
		str_level = ft_itoa(level + 1);
	if (!str_level)
		return ;
	tmp = ft_strjoin("bash: warning: shell level (", str_level);
	free(str_level);
	if (!tmp)
		return ;
	str_level = ft_strjoin(tmp, ") too high, resetting to 1$");
	free(tmp);
	if (!str_level)
		return ;
	ft_perror(str_level);
	free(str_level);
}
