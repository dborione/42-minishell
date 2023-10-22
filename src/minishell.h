/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:55:56 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/22 15:04:29 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

//# include <linux/limits.h> 
# include <sys/syslimits.h>

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

typedef	struct s_lexer_tokens
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

typedef struct s_shell_data
{
	char 		**envp;
	int			pipe[2];
	int			input_fd;
	int			output_fd;
	int			infile;
	int			outfile;
	int			exit_code;
	int			exit;
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
int				ft_get_token_from_input(char *input);
void			ft_parse_elements(t_shell_data **shell_data, t_lexer_tokens **lexer_list);

/* Commands */

typedef struct s_cmd
{
	char			*name;
	char			**args;
	char			*full;
	char			*path;
	struct s_cmd	*next;
}					t_cmd;

typedef	struct s_args_split
{
	char				*arg;
	struct s_args_split	*next;
}						t_args_list;

t_cmd			*ft_get_command(char *cmd, char **paths);
char			**ft_get_command_args(char *full_cmd);
t_args_list		*ft_new_command_arg(char *tmp);
int				ft_add_command_arg(t_args_list **cmd_split, char *tmp);

/* Args */

t_args_list		*ft_new_args_list(char *tmp);
char			**ft_split_args(char *input);
void        	ft_free_args_list(t_args_list **cmd_split);

/* Builtins */

int				ft_is_builtin(char *input);
int				ft_cd(t_shell_data **shell_data, char *input);
int				ft_env(char **envp);
int				ft_pwd(char **envp);
int				ft_echo(t_lexer_tokens *target);
int				ft_exit(t_shell_data **shell_data, char *input);

/* Quotes */

int				ft_has_endof_quotes(char *input, char quote);
char			*ft_get_with_quotes(char *str);

/* Execution */

void			ft_execution(t_shell_data *t_shell_data, t_cmd *cmd);

/* History */

void    		ft_add_to_history_file(t_shell_data *shell_data, char **hist_file, char *line);

/* Files */

int				ft_get_infile(t_shell_data **shell_data, char *tmp);
int				ft_get_outfile(t_shell_data **shell_data, char *tmp);

#endif