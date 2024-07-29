/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:15:05 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/30 01:03:01 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_lexer
{
	char			*lexer_comp;
	int				token;
	int				i;
	char			*path;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_cmd
{
	t_lexer			*lexer_list;
	char			**commands;
	int				num_commands;
	int				input_redir;
	char			*input_file;
	int				output_redir;
	char			*output_file;
	char			*heredoc;
	int				flags;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char			*env_var;
	char			*env_comp;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_lexer	*lexer_list;
	t_cmd	*cmd_list;
	t_env	*env_list;
	char	**envp;
	char	**paths;
	char	*pwd;
	char	*home;
	char	*old_pwd;
	char	*readline;
	int		pipefd[2];
	int		pipes;
	pid_t	pid;
	int		explantion;
}	t_data;

typedef struct s_signal
{
	int	in_heredoc;
	int	in_cmd;
	int	stop_heredoc;
	int	exit_status;
}	t_signal;

extern t_signal	g_signal;

# define EMPTY 0
# define ARG 1
# define CMD 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define HEREDOC 6
# define PIPE 7
# define MINICMD 8
# define START 9
# define END 10
# define AND 11
# define SEMI 12

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define IS_DIR 126
# define NOT_DIR 127

//error functions
void	ft_error(char *str, t_data *data);
int		ft_error_double_token(t_data *data, int token);
void	ft_error_exit(char *str, t_data *data);
void	ft_perror(char *str, int fd);
void	ft_error_cmd(char *str, t_data *data);
void	ft_error_export(char *str);
void	ft_error_exit_numeric(char *str, t_data *data);
void	ft_error_cd(char *str, t_data *data);
void	ft_exit_normal(t_data *data, t_lexer *lexer_list);
//void	print_t_cmd(const t_cmd *cmd);
//initialize functions
void	ft_initialize_data(t_data *data);
void	ft_reset_data(t_data *data);
int		ft_arr_len(char **arr);
int		is_whitespace(char c);
//parsing functions
void	ft_find_pwd(t_data *data);
int		ft_find_path(t_data *data);
int		ft_find_matching_quote(char *line, int index, int *count, int type);
void	ft_cmd_clear_list(t_cmd **cmd_list);
void	ft_count_pipes(t_data *data);
int		ft_count_args(t_lexer *lexer_list);
int		ft_parser(t_data *data);
t_lexer	*ft_fill_cmd(t_lexer *lexer_list, t_cmd *cmd_list, int i);
void	ft_cmd_add_back(t_cmd **cmd_list, t_cmd *new_cmd);
int		ft_check_token_start_end(char *line);
t_cmd	*ft_cmd_new(void);
int		ft_handle_pipe_error(t_data *data, t_lexer *lexer_list);
t_lexer	*ft_check_n(t_lexer *lexer_list, int *flag);

//free functions
void	ft_free_arr(char **arr);
void	ft_free_data(t_data *data);
void	ft_env_clear_list(t_env **env_list);
//Utils functions
char	**ft_arrdup(char **arr);
void	ft_arrdup_modified(t_data *data, char **arr, char *str);
int		ft_count_quotes(char *line);
char	*ft_check_quotes(char *str);
char	*remove_quotes(char *str);
//lexer functions
int		ft_handle_token(t_data *data, int index, t_lexer **lexer_list);
int		ft_lexer_add(char *readline, int type, t_lexer **lexer_list);
void	ft_lexer_add_back(t_lexer **lexer_list, t_lexer *new_lexer);
t_lexer	*ft_lexer_new(char *readline, int type);
int		ft_lexer_reader(t_data *data);
int		ft_check_token(int c);
void	ft_lexer_clear_list(t_lexer **lexer_list);
void	ft_lexer_del_one(t_lexer **lexer_list, int key);
t_lexer	*ft_lexer_clear_one(t_lexer **lexer_list);
void	ft_lexer_del_first(t_lexer **lexer_list);
void	ft_lexer_clear_list(t_lexer **lexer_list);
size_t	ft_lexer_len(t_lexer *lexer_list);
void	ft_add_env_list(char *str, t_env **env_list);
//executor functions
void	ft_exec(t_data *data, int input_fd, int output_fd);
int		ft_executor(t_data *data, t_cmd *cmd_list);
void	ft_prepare_executor(t_data *data);
void	ft_here_doc(char *limiter);

// builtins functions
void	ft_builtins_parent(t_data *data, t_cmd *cmd_list);
int		ft_builtins_child(t_data *data, t_cmd *cmd_list);
void	ft_mini_exit(t_data *data);
void	ft_mini_cd(t_data *data, t_cmd *cmd_list);
int		ft_mini_echo(t_data *data, t_cmd *cmd_list);
void	ft_mini_env(t_data *data, t_cmd *cmd_list);
void	ft_mini_export(t_data *data, t_cmd *cmd_list);
void	ft_mini_pwd(t_data *data, t_cmd *cmd_list);
void	ft_mini_unset(t_data *data, t_cmd *cmd_list);
void	ft_qsort(char **array);
void	ft_print_echo(t_data *data, t_lexer *lexer_list, int flag);
int		ft_is_exit(t_data *data);
int		ft_cmd_delete_prev(t_cmd **cmd_list, t_cmd *next_cmd);
//expander functions
void	ft_expander_echo(t_data *data, t_cmd *cmd_list, int flag);
char	*ft_strjoin_modified(char *s1, char const *s2);
void	ft_expander(t_data *data);
void	ft_get_variable(char *varibale, char **env);
//signal functions
void	ft_init_signal(void);
void	ft_clear_signal(void);
void	ft_sigint_handler(int sig);
void	ft_sigquit_handler(int sig);

#endif
