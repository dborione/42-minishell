#include "../../inc/minishell.h"

int ft_cd_errors(char *cmd_name, char *msg)
{
	ft_perror("bash: cd: ");
	ft_perror(cmd_name);
    ft_perror(msg);
    return (1);
}