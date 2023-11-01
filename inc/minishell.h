/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:55:56 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/31 17:07:56 by rbarbiot         ###   ########.fr       */
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

/* Parsing Tokens */
# define CMD 1
# define BUILTIN 2
# define SYMBOL 3
# define ENV_VAR 4
# define INVALID 5
# define CTRL_CMD 6

/* Colours */
# define GREEN [0;32m
# define BLUE [0;34m
# define DEFAULT [0;37m

/* PIPES */

# define READ_PIPE 0
# define WRITE_PIPE 1

/* SIGNAL PROCESSES */
# define MAIN 0
# define HEREDOC_CHILD 1
# define CTL_C_EXIT 1

typedef struct s_lexer_tokens
{
	char					*input;
	int						token;
	struct s_lexer_tokens	*next;
}							t_lexer_tokens;

typedef struct s_env_var
{
	char		*key;
	char		*value;
}				t_env_var;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	int				builtin;
	char			*path;
	int				id;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_args_split
{
	char				*arg;
	struct s_args_split	*next;
}						t_args_list;

typedef struct s_shell_data
{
	int	quit;
	int	pid;
	int	rl_catch_signals;
	char		**envp;
	int			pipe[2];
	int			input_fd;
	int			output_fd;
	int			infile;
	int			outfile;
	int			exit_code;
	int			exit;
	char		*prompt;
	struct		sigaction	sa;
}				t_shell_data;

/* Init */

int				ft_init_shell(t_shell_data **shell_data, char *shell_path, char *envp[]);

/* Shell Env */

char			**ft_envp_copy(char *envp[]);
char			*ft_envp_get_key(char *input);
char			*ft_envp_get_value(char **envp, char *key);
int				ft_envp_set(t_shell_data **shell_data, char **input);
int				ft_envp_add(t_shell_data **shell_data, char **input);

/* Prompt */

// int				ft_show_user_path(char **enpv);
char			*ft_show_user_path(char **envp);

/*	Input */

void			ft_get_input(t_shell_data	**shell_data);

/*	Parsing */

t_lexer_tokens *ft_parse_input(t_shell_data **shell_data, char *line);
int				ft_add_token_to_list(t_lexer_tokens **lexer_list, char **input, int token);
void			ft_free_lexer_list(t_lexer_tokens **lexer_list);
void			ft_parse_elements(t_shell_data **shell_data, t_lexer_tokens **lexer_list);

/* Commands */

t_cmd			*ft_get_command(char *cmd, char **paths, int builtin);
void			ft_add_command(t_cmd **cmds, t_cmd *new_cmd);
void			ft_free_commands(t_cmd **cmds);

/* Args */

t_args_list		*ft_new_args_list(char *tmp);
char			**ft_split_args(char *input);
t_args_list		*ft_input_to_args_list(char *input, size_t len);
int				ft_add_arg_to_list(t_args_list **cmd_split, char *tmp);
size_t			ft_split_from_quotes(
	t_args_list **cmd_split, char *str_before, char *str_after);
char			**ft_args_list_to_str_split(t_args_list **cmd_split);
void        	ft_free_args_list(t_args_list **cmd_split);

/* Builtins */

int				ft_execute_builtin(t_shell_data **shell_data, t_cmd *cmd);
int				ft_is_builtin(char *input);
int				ft_cd(t_shell_data **shell_data, t_cmd *cmd);
int				ft_env(char **envp);
int				ft_pwd(void);
int				ft_echo(char **envp, t_cmd *cmd);
int				ft_exit(t_shell_data **shell_data, t_cmd *cmd);
int				ft_export(char **envp, t_cmd *cmd);

/* Quotes */

int				ft_has_endof_quotes(char *input, char quote);
char			*ft_between_quotes(char *str);

/* Execution */

void			ft_execution(t_shell_data **t_shell_data, t_cmd **cmd);

/* History */

void    		ft_add_to_history_file(char **hist_file, char *line);

/* Files */

int				ft_get_infile(t_shell_data **shell_data, char *tmp);
int				ft_get_outfile(t_shell_data **shell_data, char *tmp);
int				ft_use_pipe(t_shell_data **shell_data, t_cmd *cmd, int pipe_fd[2]);

/* Signals */

void    		ft_init_shell_sigaction(t_shell_data *shell_data, int process);

/* Heredoc */
int				ft_heredoc(t_shell_data *shell_data, char *line);

#endif