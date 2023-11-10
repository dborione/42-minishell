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
    int j;
    char *key_env;
    char *key_arg;
    char *new_arg;

    i = -1;
    j = -1;
    new_arg = NULL;
    key_arg = NULL;
    while (arg[++j])
    {
        if (arg[j] == '+')
        {
            key_arg = malloc(sizeof(char) * (j + 1));
            ft_strlcpy(key_arg, arg, j + 1);
            break ;
        }
    }
    while (envp[++i])
    {
        if (ft_isequal(envp[i], arg))
            return (0);
        key_env = ft_envp_get_key(envp[i]);
        if (ft_isequal(key_env, key_arg))
        {
            if (arg[j] == '+')
            {
                new_arg = ft_strjoin(envp[i], &arg[j + 2]);
                free(envp[i]);
                envp[i] = new_arg;
                free (key_arg);
                return (0);
            }
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
    {
        if (ft_isequal(export_envp[j], arg))
            return (0);
        j++;
    }
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
            if (arg[i] == '=' || arg[i] == '_')
            {
                if (ft_isalnum(arg[i - 1]) || arg[i - 1] == '+')
                    return (1);
                return (0);
            }
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
            if (!ft_add_to_export_env(export_envp, cmd->args[i]) || !ft_add_to_env(envp, cmd->args[i]))
                i++;
        }
        i++;
    }
    return (1);
}
