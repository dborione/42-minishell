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
        printf("%s", current->input);
        current = current->next;
    }
    return (1);
}