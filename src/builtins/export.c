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

int ft_export(t_shell_data **shell_data, t_cmd *cmd)
{
    int     i;
	char	*tmp;

    i = 1;
    if (!cmd->args[1])
        return (ft_print_export_env((*shell_data)->export_envp));
    while (cmd->args[i])
    {
        if (!ft_check_valid_char(cmd->args[i]))
        {
            ft_export_error(cmd->args[i]);
            i++;
            if (!cmd->args[i])
                break ;
        }
		tmp = ft_strdup(cmd->args[i]);
		if (!tmp)
			return (127);
		if (!ft_envp_set(shell_data, &tmp))
		{
			free(tmp);
			return (127);
		}
		//free(tmp);
        i++;
    }
    return (0);
}
