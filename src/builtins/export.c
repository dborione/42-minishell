#include "../../inc/minishell.h"

static
int ft_print_export_env(char **envp)
{
    int	i;
    char *key;
	i = 0;
	while (envp[i])
	{
        key = ft_envp_get_key(envp[i]);
		printf("declare -x %s", key);
		printf("=");
		printf("\"%s\"\n", ft_envp_get_value(envp, key));
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
int ft_add_to_env(char **envp, char *arg)
{
    int j;

    j = 0;
    if (!ft_strrchr(arg, '='))
        return (0);
    while (envp[j])
        j++;
    envp[j] = ft_strdup(arg);
    envp[j + 1] = NULL;
    return (1);
}

static
int ft_add_to_export_env(char **envp, char **export_env_copy, char *arg)
{
    int j;

    j = 0;
    export_env_copy = ft_envp_copy(envp);
    while (export_env_copy[j])
        j++;
    export_env_copy[j] = ft_strdup(arg);
    export_env_copy[j + 1] = NULL;
    return (1);
}

int ft_export(char **envp, char **export_env, t_cmd *cmd)
{
    int     i;

    i = 1;
    if (!export_env)
    {
        export_env = ft_envp_copy(envp);
        if (!export_env)
        {
            printf("export env copy error\n");
            return (0);
        }
    }
    if (!cmd->args[1])
        return (ft_print_export_env(export_env));
    while (cmd->args[i])
    {
        if (!ft_isalpha(cmd->args[i][0]))
            return (ft_export_error(cmd->args[i]));
        if (ft_is_in_env(envp, cmd->args[i]))
        {
            ft_add_to_export_env(envp, export_env, cmd->args[i]);
            if (!ft_add_to_env(envp, cmd->args[i]))
                i++;
            if (!cmd->args[i])
                break ;
        }
        else
            i++;
    }
    // free export env
    return (1);
}
