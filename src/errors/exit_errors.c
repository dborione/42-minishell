#include "../../inc/minishell.h"

int ft_exit_num_msg(t_shell_data **shell_data, t_cmd *cmd)
{
	ft_perror("bash: exit: ");
	ft_perror(cmd->args[1]);
	ft_perror(": numeric argument required\n");
	(*shell_data)->exit_code = 255;
	return ((*shell_data)->exit_code);
}

int ft_exit_arg_msg(t_shell_data **shell_data)
{
	ft_perror("bash: exit: too many arguments.");
	(*shell_data)->exit_code = 1;
	return ((*shell_data)->exit_code);
}