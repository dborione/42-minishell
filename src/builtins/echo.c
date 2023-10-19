#include "../minishell.h"

int ft_echo(t_lexer_tokens *target)
{
    t_lexer_tokens *current;

    // voir pour les redirections
    current = target;
    if (!current->next)
    {
        printf("\n");
        return (1);
    }
    current = current->next;
    while (current)
    {   
        // if (!ft_strncmp(current->next->input, ">", 1) && ft_strlen(current->next->input) == 1)
        // {
        //      char *arg = current->input;
        //      current = current->next;
        //      
        // }
        printf("%s", current->input);
        current = current->next;
    }
    return (1);
}