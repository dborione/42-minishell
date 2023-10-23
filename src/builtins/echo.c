#include "../minishell.h"

int ft_echo(char **envp, t_cmd *cmd)
{
	int	i;
    // t_lexer_tokens *current;

    // // voir pour les redirections
    // current = target;
    // if (!current->next)
    // {
    //     printf("\n");
    //     return (1);
    // }
    // current = current->next;
    // while (current)
    // {   
    //     // if (!ft_strncmp(current->next->input, ">", 1) && ft_strlen(current->next->input) == 1)
    //     // {
    //     //      char *arg = current->input;
    //     //      current = current->next;
    //     //      
    //     // }
    //     printf("%s", current->input);
    //     current = current->next;
    // }
	i = 1;
	while(cmd->args[i])
	{
		if (i > 1)
			ft_putchar_fd(' ', 1);
		ft_printf(cmd->args[i]);
		i++;
	}
	ft_putendl_fd("", 1);
	if (cmd && envp)
    	return (1);
	return (1);
}