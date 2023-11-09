/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:55:56 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/09 11:14:43 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h> // pour ne pas afficher ^C
# include "ft_limits.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

/* Colours */
# define GREEN \033[0;92m
# define BLUE \033[0;34m
# define DEFAULT \033[0;37m

/* PIPES */

# define READ_PIPE 0
# define WRITE_PIPE 1

/* SIGNAL PROCESSES */
# define MAIN 0
# define HEREDOC_CHILD 2
# define CTL_C_EXIT 99

typedef struct s_env_var
{
	char		*key;
	char		*value;
}				t_env_var;

typedef struct s_cmd
{
	char			*name;
	size_t			id;
	char			**args;
	int				builtin;
	int				input_fd;
	int				output_fd;
	char			*path;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_args_split
{
	char				*value;
	int					separator;
	struct s_args_split	*next;
}						t_args_list;

typedef struct s_data_split
{
	char	*tmp;
	size_t	i;
	size_t	start;
	char	**envp;
	int		exit_code;
	int		space;
}			t_data_split;

typedef struct s_lasso
{
	size_t					index;
	size_t					start;
	size_t					end;
	struct s_ignore_index	*next;
}				t_lasso;

typedef struct s_ignore_index
{
	size_t					index;
	struct s_ignore_index	*next;
}				t_ignore_index;

typedef struct s_shell_data
{
	int					exec;
	int					rl_catch_signals;
	char				**envp;
	char				**export_envp;
	int					pipe[2];
	size_t				pipes;
	int					input_fd;
	int					output_fd;
	int					infile;
	int					outfile;
	int					exit_code;
	int					exit;
	char				*prompt;
	t_ignore_index		*ignore_index;
	t_lasso				*lassos;
	struct sigaction	sa;
}				t_shell_data;

/* Init */

int				ft_init_shell(
					t_shell_data **shell_data, char *shell_path, char *envp[]);

/* Shell Env */

char			**ft_envp_copy(char *envp[]);
char			*ft_envp_get_key(char *input);
char			*ft_envp_get_value(char **envp, char *key);
int				ft_envp_set(t_shell_data **shell_data, char **input);
int				ft_envp_add(t_shell_data **shell_data, char **input);
char			*ft_include_var(t_data_split *data, char *input);

/* Prompt */

char			*ft_show_user_path(char **envp);

/*	Input */

void			ft_get_input(t_shell_data	**shell_data);

/*	Parsing */

t_cmd			*ft_parse_input(t_shell_data **shell_data, t_args_list *args);

/* Commands */

t_cmd			*ft_get_command(t_args_list *args, char **paths);
size_t			ft_add_command(t_cmd **cmds, t_args_list *args, char **paths);
void			ft_free_commands(t_cmd **cmds);

/* Args */

t_args_list		*ft_new_args_list(char *tmp);
t_args_list		*ft_split_args(t_shell_data **shell_data, char *input);
t_args_list		*ft_input_to_args_list(
					t_shell_data **shell_data, char *input, size_t len);
int				ft_add_arg_to_list(t_args_list **cmd_split, char *tmp);
int				ft_join_args(t_args_list **cmd_split, char *tmp);
int				ft_one_split(
					t_data_split **data, t_args_list **args_list,
					char *input, char *tmp);
char			**ft_args_list_to_str_split(t_args_list **cmd_split);
void			ft_free_args_list(t_args_list **cmd_split);
void			*ft_exit_split_args(
					t_data_split **data, t_args_list **args_list);
int				ft_is_invalid_args_separator(
					t_shell_data **shell_data, char *input);
int				ft_split_char_separator(
					t_data_split **data, t_args_list **args_list,
					char *input, char separator);
int				ft_split_string_separator(
					t_data_split **data, t_args_list **args_list,
					char *input, char *separator);
char			**ft_extract_args(t_args_list *args);

/* Args Spaces */

int				ft_space_split(
					t_data_split **data, t_args_list **args_list, char *input);

/* Args Quotes */

int				ft_has_endof_quotes(char *input, char quote);
char			*ft_between_quotes(char *str);
int				ft_quotes_split(
					t_data_split **data, t_args_list **args_list, char *input);
size_t			ft_join_from_quotes(
					t_data_split *data, t_args_list **cmd_split, char *str_before, char *str_after);
size_t			ft_split_from_quotes(
					t_data_split *data, t_args_list **cmd_split, char *input);

/* Builtins */

int				ft_execute_builtin(t_shell_data **shell_data, t_cmd *cmd);
int				ft_is_builtin(char *input);
int				ft_cd(t_shell_data **shell_data, t_cmd *cmd);
int				ft_env(char **envp);
int				ft_pwd(void);
int				ft_echo(char **envp, t_cmd *cmd);
int				ft_exit(t_shell_data **shell_data, t_cmd *cmd);
int				ft_export(char **envp, char **export_env, t_cmd *cmd);
int				ft_unset(char **envp, char **export_envp, t_cmd *cmd);

/* Execution */

void			ft_execution(t_shell_data **t_shell_data, t_cmd **cmd);

/* History */

void			ft_add_to_history_file(char **hist_file, char *line);

/* Files */

int				ft_get_infile(
					t_shell_data **shell_data, t_cmd *cmds, char *infile_path);
int				ft_get_outfile(
					t_shell_data **shell_data, t_cmd *cmds, char *tmp);
int				ft_use_pipe(
					t_shell_data **shell_data, t_cmd *cmd, int pipe_fd[2]);
void			ft_reset_fd(t_shell_data **shell_data);

/* Signals */

void			ft_init_shell_sigaction(t_shell_data *shell_data, int process);

/* Heredoc */

int	ft_heredoc(t_shell_data *shell_data, t_args_list *target);


/* Errors */

int				ft_perror(char *message);
void			ft_wrong_tokens_syntax(t_shell_data **shell_data, char token);
void			ft_wrong_redirection_syntax(t_shell_data **shell_data);
void			ft_command_not_found(char *cmd_name);
int				ft_export_error(char *arg);
int				ft_exit_num_msg(t_shell_data **shell_data, t_cmd *cmd);
int				ft_exit_arg_msg(t_shell_data **shell_data);

#endif