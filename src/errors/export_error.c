#include "../../inc/minishell.h"

int	ft_export_error(char *arg)
{
    ft_perror("bash: export: `");
	ft_perror(arg);
	ft_perror("': not a valid identifier\n");
    return (1);
}