#include "../../inc/minishell.h"

int ft_echo(char **envp, t_cmd *cmd)
{
	int i;
	int	new_line;

	i = 1;
	new_line = 0;
	if (ft_startswith("-n", cmd->args[i]))
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
    	return (1);
	return (1);
}
