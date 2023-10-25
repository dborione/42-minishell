#include "../../inc/minishell.h"

void    ft_add_to_history_file(char **hist_file, char *line)
{
	int		hist_fd;

    hist_fd = open(*hist_file, O_CREAT | O_APPEND, 0777);
    if (hist_fd == -1)
    {
        ft_printf("history error\n");
        return ;
    }
	add_history(line);
    write_history(*hist_file);
    close(hist_fd);
}