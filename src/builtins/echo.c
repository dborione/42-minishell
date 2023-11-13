#include "../../inc/minishell.h"

static
int	ft_is_n_option(char *input)
{
	size_t	i;

	if (!ft_startswith(input, "-n"))
		return (0);
	i = 2;
	while (input[i])
	{
		if (input[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static
void	ft_skip_n_options(char **args, int *i)
{
	(*i)++;
	while (ft_is_n_option(args[*i]))
		(*i)++;
}

int ft_echo(char **envp, t_cmd *cmd)
{
	int i;
	int	new_line;
	int	start;
	char *tmp;

	i = 1;
	new_line = 0;
	if (ft_is_n_option(cmd->args[i]))
		ft_skip_n_options(cmd->args, &i);
	else
		new_line = 1;
	start = i;
	while (cmd->args[i])
	{
		if ((new_line && i > start) || (!new_line && i > start))
			ft_putchar_fd(' ', 1);
		if (ft_startswith(cmd->args[i], "~/") || ft_isequal(cmd->args[i], "~"))
		{
			tmp = ft_strjoin(ft_envp_get_value(envp, "HOME"), &cmd->args[i][1]); // a voir quand HOME est unset
			ft_printf(tmp);
			free(tmp);
			i++;
			if (!cmd->args[i])
				break ;
		}
		ft_printf(cmd->args[i]);
		i++;
	}
	if (new_line)
		ft_putendl_fd("", 1);
	if (cmd && envp)
    	return (0);
	return (0);
}
