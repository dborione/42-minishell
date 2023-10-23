#include "../minishell.h"

int ft_echo(char **envp, t_cmd *cmd)
{
	int i;
	int	new_line;

	// retirer la newline avec l'option -n 
	i = 1;
	new_line = 1;
	if (ft_isequal("-n", cmd->args[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd->args[i])
	{
		if (new_line == 1 && i > 1)
			ft_putchar_fd(' ', 1);
		ft_printf(cmd->args[i]);
		if (new_line == 0)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line == 1)
		ft_putendl_fd("", 1);
	if (cmd && envp)
    	return (1);
	return (1);
}
