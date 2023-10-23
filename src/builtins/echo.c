#include "../minishell.h"

int ft_echo(char **envp, t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd->args[i])
	{
		if (i > 1)
			ft_putchar_fd(' ', 1);
		ft_printf(cmd->args[i]);
		i++;
	}
	ft_putendl_fd("", 1);
	if (cmd && envp)
    	return (1);
	return (1);
}
