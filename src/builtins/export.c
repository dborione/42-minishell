#include "../../inc/minishell.h"

int ft_export(char **envp, t_cmd *cmd)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (envp[j])
        j++;
    while (cmd->args[i])
    {
        //envp[j] = malloc (sizeof(cmd->args));
        envp[j] = ft_strdup(cmd->args[i]);
        j++;
        i++;
    }
    //printf("%s\n", envp[j]);
    //printf("%s\n", envp[j - 1]);
    return (1);
}