/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:55:56 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/11/17 17:38:51 by dborione         ###   ########.fr       */
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
# include <dirent.h>
# include <errno.h>

/* PIPES */

# define READ_PIPE 0
# define WRITE_PIPE 1

/* SIGNAL PROCESSES */
# define MAIN 0
# define HEREDOC_CHILD 2
# define CTL_C_EXIT 1

# define FALSE 0
# define TRUE 1

typedef struct s_env_var
{
	char		*key;
	char		*value;
}				t_env_var;

typedef struct s_cmd
{
	char			*name;
	size_t			id;
	pid_t			pid;
	char			**args;
	int				builtin;
	int				input_target_fd;
	int				input_fd;
	int				output_source_fd;
	int				output_fd;
	char			*path;
	int				exit_code;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_args_split
{
	char				*value;
	int					separator;
	int					fd;
	struct s_args_split	*next;
}						t_args_list;

typedef struct s_data_split
{
	char	*tmp;
	size_t	i;
	size_t	start;
	char	**envp;
	char	*home;
	int		exit_code;
	int		space;
}			t_data_split;

typedef struct s_data_include_var
{
	size_t	i;
	size_t	start;
	size_t	len;
	int		quotes;
	char	*res;
}			t_data_include_var;

typedef struct s_shell_data
{
	int					exec;
	int					rl_catch_signals;
	char				**envp;
	char				**private_envp;
	int					pipe[2];
	size_t				pipes;
	char				*pwd;
	char				*home;
	int					input_target_fd;
	int					input_fd;
	int					output_source_fd;
	int					output_fd;
	int					infile;
	int					outfile;
	int					exit_code;
	int					exit;
	char				*prompt;
	char				**paths;
	t_cmd				*cmds;
	struct sigaction	sa;
}				t_shell_data;

/* Init */

int				ft_init_all(t_shell_data **shell_data, 
					char *envp[], char *shell_path);
int				ft_init_shell(t_shell_data **shell_data, 
					char *envp[], char *shell_path);
int				ft_init_envp(t_shell_data **shell_data, 
					char **envp, char *shell_path);
void			ft_init_shell_sigaction(t_shell_data *shell_data, int process);
void			ft_destroy_shell(t_shell_data **shell_data);

/* Shell Env */

char			**ft_envp_copy(char *envp[]);
char			*ft_envp_get_key(char *input);
char			*ft_envp_get_value(char **envp, char *key);
char			*ft_var_get_value(char *var);
char			*ft_envp_get_var(char **envp, char *var);
char			*ft_var_new_value(char *var, char *old_var);
int				ft_export_env(t_shell_data **shell_data);
int				ft_env_same_key(char *key, char *var);
int				ft_env_has(char **envp, char *key);
int				ft_private_envp_set(t_shell_data **shell_data, char *input);
int				ft_envp_set(t_shell_data **shell_data, char *input);
int				ft_private_envp_add(t_shell_data **shell_data, char *input);
int				ft_envp_add(t_shell_data **shell_data, char *input);
int				ft_envp_unset(t_shell_data **shell_data, char *key);
int				ft_private_envp_unset(t_shell_data **shell_data, char *key);
char			*ft_envp_get_home(t_shell_data *shell_data);
int				ft_check_shell_health(t_shell_data *shell_data);

/* Include Var */

char			**ft_include_var(t_data_split *data, char *input, int quotes);
int				ft_is_var_char(char c);
char			*ft_get_value(t_data_split *data, char *str, size_t end);
char			*ft_var_join(char *s1, char *s2, size_t len);
int				ft_include_envp_var(
					t_data_split *data, char *input, 
					t_data_include_var **data_i);
int				ft_include_home(
					t_data_split *data, char *input, 
					t_data_include_var **data_i);
int				ft_include_envp_var(
					t_data_split *data, char *input, 
					t_data_include_var **data_i);
int				ft_include_var_split(t_args_list **args, char **var_split);

/* Prompt */

char			*ft_show_user_path(char **envp);

/*	Input */

void			ft_get_input(t_shell_data	**shell_data);
int				ft_ends_with_pipe(t_args_list *args);
int				ft_invalide_start(
					t_shell_data **shell_data, t_args_list **args);
int				ft_add_more_inputs(
					t_shell_data **shell_data, t_args_list **args_list);

/*	Parsing */

t_cmd			*ft_parse_input(t_shell_data **shell_data, t_args_list *args);
int				ft_parse_separator(
					t_shell_data **shell_data, t_cmd **cmds, 
					t_args_list **target, int *skip);
int				ft_is_empty_line(char *line);
int				ft_set_res(t_shell_data **shell_data, int res);

/* Commands */

t_cmd			*ft_get_command(t_args_list *args, char **paths);
size_t			ft_add_command(t_cmd **cmds, t_args_list *args, char **paths);
void			ft_set_command_fds(t_shell_data **shell_data, t_cmd *cmds);
void			ft_free_commands(t_cmd **cmds);
int				ft_set_path(t_cmd *new_cmd, char **paths);

/* Args */

t_args_list		*ft_new_args_list(char *tmp);
t_args_list		*ft_split_args(t_shell_data **shell_data, char *input);
t_args_list		*ft_input_to_args_list(
					t_shell_data **shell_data, char *input, size_t len);
int				ft_split_checker(t_shell_data **shell_data, t_data_split **data,
					t_args_list **args_list, char *input);
int				ft_add_arg_to_list(t_args_list **cmd_split, char *tmp);
int				ft_join_args(t_args_list **cmd_split, char *tmp);
int				ft_one_split(
					t_data_split **data, t_args_list **args_list,
					char *input, char *tmp);
char			**ft_args_list_to_str_split(t_args_list **cmd_split);
void			ft_free_args_list(t_args_list **cmd_split);
void			*ft_exit_split_args(
					t_data_split **data, t_args_list **args_list);
int				ft_is_speparators(char *input);
int				ft_is_invalid_args_separator(
					t_shell_data **shell_data, char *input);
int				ft_split_char_separator(
					t_data_split **data, t_args_list **args_list,
					char *input, char separator);
int				ft_split_string_separator(
					t_data_split **data, t_args_list **args_list,
					char *input, char *separator);
int				ft_last_arg(t_data_split *data, t_args_list **args_list);
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
					t_data_split *data, t_args_list **cmd_split, 
					char *str_before, char *str_after);
size_t			ft_split_from_quotes(
					t_data_split *data, t_args_list **cmd_split, char *input);

/* Builtins */

int				ft_is_builtin(char *input);
int				ft_cd(t_shell_data **shell_data, t_cmd *cmd);
int				ft_env(char **envp);
int				ft_pwd(t_shell_data *shell_data);
int				ft_echo(char **envp, t_cmd *cmd);
int				ft_exit(t_shell_data **shell_data, t_cmd *cmd);
int				ft_export(t_shell_data **shell_env, t_cmd *cmd);
int				ft_unset(t_shell_data **shell_data, t_cmd *cmd);

/* Execution */

void			ft_execution(t_shell_data **t_shell_data, t_cmd **cmd);
void			ft_next_execution(t_shell_data **shell_data, t_cmd *cmd);
int				ft_execute_builtin(t_shell_data **shell_data, 
					t_cmd *cmd, int sub_process);

/* History */

void			ft_add_to_history_file(char **hist_file, char *line);

/* Files */

int				ft_get_infile(
					t_shell_data **shell_data, t_cmd *cmds, char *infile_path);
int				ft_get_outfile(
					t_shell_data **shell_data, t_cmd *cmds, 
					char *outfile_path, int append);
int				ft_use_pipe(
					t_shell_data **shell_data, t_cmd *cmd, int pipe_fd[2]);
void			ft_reset_fd(t_shell_data **shell_data);
char			*ft_get_shell_path(char **envp, char *shell_relative_path);
int				ft_change_pwds(t_shell_data **shell_data, char *target_dir);

/* Heredoc */

int				ft_heredoc(t_shell_data *shell_data, char *eof);

/* Errors */

int				ft_perror(char *message);
void			ft_wrong_tokens_syntax(t_shell_data **shell_data, char *token);
void			ft_wrong_redirection_syntax(t_shell_data *shell_data);
void			ft_command_not_found(char *cmd_name);
int				ft_export_error(char *arg);
int				ft_exit_num_msg(t_shell_data **shell_data, t_cmd *cmd);
int				ft_exit_arg_msg(t_shell_data **shell_data);
void			ft_no_such_file(char *cmd_name);
void			ft_perm_denied(char *cmd_name);
void			ft_shlvl_to_hight(int level);
void			ft_memory_error(t_shell_data **shell_data);
int				ft_cd_errors(char *cmd_name, char *msg);
int				ft_dup2_error(t_shell_data **shell_data, int pipe);

#endif
