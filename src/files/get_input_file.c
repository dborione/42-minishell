/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:46:57 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 15:37:27 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_get_infile(t_shell_data **shell_data, char *tmp)
{
	char	*infile_path;

	infile_path = ft_strtrim(tmp, " ");
	if (!infile_path)
		return (0);
	ft_printf("infile: %s\n", infile_path);
	if ((*shell_data)->infile)
		close((*shell_data)->input_fd);
	if (access(infile_path, F_OK) == 0 && access(infile_path, R_OK) == 0)
	{
		(*shell_data)->input_fd = open(infile_path, O_RDONLY, 0644);
		if ((*shell_data)->input_fd == -1)
		{
			(*shell_data)->exit_code = EXIT_FAILURE;
			return (0);
		}
		return (1);
	}
	return (0);
}
