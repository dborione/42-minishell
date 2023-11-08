#include "../../inc/minishell.h"

static
int ft_print_export_env(char **envp)
{
    int     i;
    char    *key;
    char    *value;

	i = 0;
	while (envp[i])
	{
        key = ft_envp_get_key(envp[i]);
		printf("declare -x %s", key);
        value = ft_envp_get_value(envp, key);
        if (value[0])
        {
		    printf("=");
		    printf("\"%s\"", value);
        }
		printf("\n");
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
        if (ft_isequal(envp[i], arg))
            return (0);
        key_env = ft_envp_get_key(envp[i]);
        key_arg = ft_envp_get_key(arg);
        if (ft_isequal(key_env, key_arg))
        {
            free (envp[i]);
            envp[i]= NULL;
            return (1);
        }
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
int ft_add_to_export_env(char **export_envp, char *arg)
{
    int j;

    j = 0;
    while (export_envp[j])
        j++;
    export_envp[j] = ft_strdup(arg);
    export_envp[j + 1] = NULL;
    return (1);
}

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
            if (arg[i] != '=')
                return (0);
        }
        i++;
    }
    return (1);
}

int ft_export(char **envp, char **export_envp, t_cmd *cmd)
{
    int     i;

    i = 1;
    if (!cmd->args[1])
        return (ft_print_export_env(export_envp));
    while (cmd->args[i])
    {
        if (!ft_check_valid_char(cmd->args[i]))
        {
            ft_export_error(cmd->args[i]);
            i++;
            if (!cmd->args[i])
                break ;
        }
        if (ft_is_in_env(envp, cmd->args[i]) && ft_is_in_env(export_envp, cmd->args[i]))
        {
            ft_add_to_export_env(export_envp, cmd->args[i]);
            if (!ft_add_to_env(envp, cmd->args[i]))
                i++;
        }
        i++;
    }
    return (1);
}
