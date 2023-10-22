/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:46:57 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 13:10:19 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_infile(t_shell_data **shell_data, char *tmp)
{
	char	*infile_path;

	infile_path = ft_strtrim(tmp, " ");
	if (!infile_path)
		return (0);
	ft_printf("infile: %s\n", infile_path);
	if (access(infile_path, F_OK) == 0 && access(infile_path, R_OK) == 0)
	{
		(*shell_data)->input_fd = open(infile_path, O_RDONLY, 0644);
		if ((*shell_data)->input_fd == -1)
			return (0);
		return (1);
	}
	return (0);
}
