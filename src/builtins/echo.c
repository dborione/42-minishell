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
		ft_printf(cmd->args[i]);
		i++;
	}
	if (new_line)
		ft_putendl_fd("", 1);
	if (cmd && envp)
    	return (0);
	return (0);
}
