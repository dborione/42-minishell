#include "../../inc/minishell.h"

static
int	ft_is_n_option(char *input)
{
	size_t	i;

	if (!ft_startswith("-n", input))
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

int ft_echo(char **envp, t_cmd *cmd)
{
	int i;
	int	new_line;

	i = 1;
	new_line = 0;
	if (ft_is_n_option(cmd->args[i]))
		i++;
	else
		new_line = 1;
	while (cmd->args[i])
	{
		if ((new_line && i > 1) || (!new_line && i > 2))
			ft_putchar_fd(' ', 1);
		ft_printf(cmd->args[i]);
		i++;
	}
	if (new_line)
		ft_putendl_fd("", 1);
	if (cmd && envp)
    	return (0);
	return (0);
}
