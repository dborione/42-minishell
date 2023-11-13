#include "../../inc/minishell.h"

static
void	ft_print_export_env(char **envp)
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
}

static
int		ft_export_env(t_shell_data **shell_data)
{
	ft_free_split((*shell_data)->envp);
	(*shell_data)->envp = ft_envp_copy((*shell_data)->private_envp);
	if (!(*shell_data)->envp)
		return (0);
	ft_print_export_env((*shell_data)->envp);
	return (1);
}

static
int		ft_check_valid_char(char *arg)
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

int		ft_export(t_shell_data **shell_data, t_cmd *cmd)
{
    int     i;

    i = 1;
    if (!cmd->args[1])
        return (ft_export_env(shell_data));
    while (cmd->args[i])
    {
        if (!ft_check_valid_char(cmd->args[i]))
        {
            ft_export_error(cmd->args[i++]);
            if (!cmd->args[i])
                return (1);
        }
		if (!ft_envp_set(shell_data, cmd->args[i]) || !ft_private_envp_set(shell_data, cmd->args[i]))
			return (127);
        i++;
    }
    return (0);
}
