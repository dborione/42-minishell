#include "../minishell.h"

void    ft_add_to_history_file(t_shell_data *shell_data, char **hist_file, char *line)
{
	int		hist_fd;
    //int     exp_result;

    hist_fd = open(*hist_file, O_CREAT | O_APPEND, 0777);
    if (hist_fd == -1)
    {
        printf("error");
        return ;
    }
    // exp_result = history_expand(line, &expansion);
    // if (exp_result == 1)
    // {
    // }
	add_history(line);
	//ft_show_user_path(shell_data->envp);
    write_history(*hist_file);
    //free(expansion);
    close(hist_fd);
	if (shell_data) // juste pour retirer l'erreur de compile
	{

	}
}