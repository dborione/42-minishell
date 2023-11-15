#include "../../inc/minishell.h"

void	ft_memory_error(t_shell_data **shell_data)
{
    ft_perror("bash: fork: Cannot allocate memory");
	(*shell_data)->exit_code = 127;
}