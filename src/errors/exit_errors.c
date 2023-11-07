#include "../../inc/minishell.h"

int ft_exit_num_msg(t_shell_data **shell_data, t_cmd *cmd)
{
	ft_putstr_fd("bash: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	(*shell_data)->exit_code = 255;
	return ((*shell_data)->exit_code);
}

int ft_exit_arg_msg(t_shell_data **shell_data, t_cmd *cmd)
{
	ft_putendl_fd("bash: exit: too many arguments.", STDERR_FILENO);
	(*shell_data)->exit_code = 1;
	return ((*shell_data)->exit_code);
}