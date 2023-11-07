/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:18:21 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/02 21:14:02 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static
char	*ft_get_absolute_path(char **envp, char *shell_name)
{
	char	*absolute_shell_path;
	char	*pwd;
	char	*tmp;

	tmp = NULL;
	pwd = ft_envp_get_value(envp, "PWD");
	if (!ft_endswith(pwd, "/"))
	{
		tmp = ft_strjoin(pwd, "/");
		if (!tmp)
			return (NULL);
		pwd = tmp;
	}
	absolute_shell_path = ft_strjoin(pwd, shell_name);
	if (tmp)
		free(tmp);
	return (absolute_shell_path);
}

static int	ft_set_shell_path(
	t_shell_data **shell_data, char *relative_shell_path)
{
	char	**split_path;
	char	*absolute_shell_path;
	char	*input;
	size_t	i;

	split_path = ft_split(relative_shell_path, '/');
	if (!split_path)
		return (0);
	i = 0;
	while (split_path[i] && split_path[i + 1])
		i++;
	absolute_shell_path = ft_get_absolute_path((*shell_data)->envp, split_path[i]);
	ft_free_split(split_path);
	input = ft_strjoin("SHELL=", absolute_shell_path);
	if (!input) // maybe some leaks here
	{
		free(absolute_shell_path);
		return (0);
	}
	if (!ft_envp_set(shell_data, &input))
	{
		free(input);
		free(absolute_shell_path);
		return (0);
	}
	free(absolute_shell_path);
	return (1);
}

static
int	ft_init_defaults(t_shell_data **shell_data, char *envp[])
{
	*shell_data = malloc(sizeof(t_shell_data));
	if (!shell_data)
		return (0);
	(*shell_data)->envp = ft_envp_copy(envp);
	if (!(*shell_data)->envp)
	{
		free(*shell_data);
		return (0);
	}
    (*shell_data)->export_envp = ft_envp_copy((*shell_data)->envp);
	if (!(*shell_data)->export_envp)
	{
		free(*shell_data);
		return (0);
	}
	(*shell_data)->input_fd = STDIN_FILENO;
	(*shell_data)->output_fd = STDOUT_FILENO;
	(*shell_data)->infile = 0;
	(*shell_data)->outfile = 0;
	(*shell_data)->exit_code = 0;
	(*shell_data)->exit = 0;
	(*shell_data)->prompt = NULL;
	return (1);
}

int	ft_init_shell(
	t_shell_data **shell_data, char *shell_path, char *envp[]
)
{
	if (!ft_init_defaults(shell_data, envp))
		return (0);
	if (!ft_set_shell_path(shell_data, shell_path))
	{
		free((*shell_data)->envp);
		free((*shell_data)->export_envp);
		free(shell_data);
		return (0);
	}
	return (1);
}
	// if (!ft_init_private_env)
	// {
	// 	ft_destroy_env(shell_env);
	// 	ft_destroy_env(private_env);
	// 	return (0);
	// }
// 	return (1);
// }
