#include "../minishell.h"

static
int	ft_echo_print_input(char **printed_input, int fd, int new_line)
{
	int	j;

	j = 0;
	while (printed_input[j])
	{
    	ft_putstr_fd(printed_input[j], fd);
		if (printed_input[j + 1])
            ft_putstr_fd(" ", fd);
		j++;
	}
	if (new_line == 1)
        printf("\n");
	return (1);
}

static
int	ft_echo_no_arg(char **split_input)
{
	printf("blank:");
    printf("\n");
	ft_free_split(split_input);
	// free (split_input)
    return (1);
}

static
int ft_redirect_input(char *split_input, char **printed_input)
{
    int outfile_fd;

    outfile_fd = open(split_input, O_CREAT | O_WRONLY);
    if (outfile_fd == -1)
        return (0); // protect
    // ft_putstr_fd(input), outfile_fd);
    //ft_echo_print_input(printed_input, outfile_fd);
	close(outfile_fd);
	return (1);
}


int ft_echo(t_lexer_tokens *target)
{
    char    **split_input;
    char    **printed_input;
    int		i;
	int		j;
    int		new_line;

	int	test_fd;
	test_fd = 0;
    //printf("hello:\n");
    split_input = ft_split_args(target->input);
    if (!split_input)
        return (0); // a proteger
	i = -1;
	while (split_input[++i]) ;
	printed_input = malloc(sizeof(char**) * (i + 1));
	if (!printed_input)
	{
		// free (split_input)
		return (0);
	}
    i = 1;
    if (!split_input[i])
		return (ft_echo_no_arg(split_input));
    new_line = 1;
    if (ft_isequal("-n", split_input[i]))
    {
		// printf("nl: ");
        i += i;
        new_line = 0;
    }
	j = 0;
    while (split_input[i])
    {
        // if (ft_isequal(">", split_input[i]))
        // {
    	// 	printf("bonjour:\n");
		// 	//ft_redirect_input(split_input[++i], printed_input);
		// 	// free split_input
		// 	// free printed_input
		// 	return (0);
		// }
		printed_input[j] = ft_strdup(split_input[i]);
		if (!printed_input[j])
		{
			printf("test");
			// free (split_input)
			return (0); // protect
		}
		j++;
		i++;
	}
	printed_input[j] = NULL;
	ft_echo_print_input(printed_input, STDOUT_FILENO, new_line);

    // free(split_input)
    // free (printed_input)
	return (1);
}
