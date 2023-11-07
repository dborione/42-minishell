#include "../../inc/minishell.h"

int	ft_export_error(char *arg)
{
    ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
    return (1);
}