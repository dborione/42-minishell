#include "../../inc/minishell.h"

static
int ft_check_valid_char(char *arg)
{
    int i;

    i = 0;
    if (!ft_isalpha(arg[0]))
        return (0);
    while (arg[i])
    {
        if (!ft_isalnum(arg[i]))
        {
            if (arg[i] == '=' || arg[i] == '_')
                return (1);
            return (0);
        }
        i++;
    }
    return (1);
}

static
int ft_is_in_env(char **envp, char *arg)
{
    int i;
    char *key_env;
    char *key_arg;

    i = -1;
    while (envp[++i])
    {
        key_env = ft_envp_get_key(envp[i]);
        if (!key_env)
            return (0);
        key_arg = ft_envp_get_key(arg);
        if (!key_arg)
        {
            free (key_env);
            return (0);
        }
        if (ft_isequal(key_env, key_arg))
        {
            free (key_arg);
            free (key_env);
            free (envp[i]);
            envp[i]= NULL;
            return (1);
        }
    }
    return (1);
}

int ft_unset(char **envp, char **export_envp, t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->args[++i])
    {
        if (!ft_check_valid_char(cmd->args[i]))
        {
            ft_export_error(cmd->args[i]);
            ++i;
            if (!cmd->args[i])
                break ;
        }
        if (!ft_is_in_env(envp, cmd->args[i])
            || ft_is_in_env(export_envp, cmd->args[i]))
            return (1);
    }
    return (0);
}