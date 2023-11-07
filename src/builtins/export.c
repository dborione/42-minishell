#include "../../inc/minishell.h"

static
int ft_print_export_env(char **envp)
{
    int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(envp[i], 1);
		i++;
	}
    return (1);
}

static
int ft_is_in_env(char **envp, char *arg)
{
    int i;

    i = -1;
    while (envp[++i])
    {
        if (ft_isequal(envp[i], arg))
            return (0);
    }
    return (1);
}

static
void ft_add_to_env(char **envp, char *arg)
{
    int j;

    j = 0;
    while (envp[j])
        j++;
    envp[j] = ft_strdup(arg);
    envp[j + 1] = NULL;
}

int ft_export(char **envp, t_cmd *cmd)
{
    int     i;
	char    **export_env_copy;

    i = 1;
    export_env_copy = ft_envp_copy(envp);
    if (!export_env_copy)
    {
        printf("export env copy error\n");
        return (0);
    }
    if (!cmd->args[1])
        return (ft_print_export_env(export_env_copy));
    while (cmd->args[i])
    {
        if (!ft_is_in_env(envp, cmd->args[i]))
            i++;
        if (!cmd->args[i])
            break ;
        if (!ft_strrchr(cmd->args[i], '='))
            i++;
        if (!cmd->args[i])
            break ;
        ft_add_to_env(envp, cmd->args[i]);
        i++;
    }
    return (1);
}