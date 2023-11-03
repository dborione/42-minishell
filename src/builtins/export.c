#include "../../inc/minishell.h"

int ft_export(char **envp, t_cmd *cmd)
{
    int i;
    int j;
    int equal_count;
    //char **var;

    i = 1;
    j = 0;
    equal_count = 0;
    while (cmd->args[1][j])
    {
        if (cmd->args[1][j] == '=')
            equal_count++;
        j++;
    }
    // if (equal_count == 1)
    //     var = ft_split(cmd->args[1], '=');
    // else
    if (equal_count != 1)
        return (0);
    //while (cmd->args[i])
    while(envp[i])
        i++;
    envp[i] = ft_strdup(cmd->args[1]);
    return (1);
}