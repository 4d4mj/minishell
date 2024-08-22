/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:15:05 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 00:32:24 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include "../libraries/libft/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>

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
	char			**input_file;
	int				output_redir;
	char			**output_file;
	char			**heredoc;
	int				heredoc_num;
	int				heredoc_index;
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
	char	**old_envp;
	char	**paths;
	char	*pwd;
	char	*home;
	char	*old_pwd;
	char	*readline;
	int		exit_status;
	int		pipes;
	int		explanation;
	int		quote_heredoc;
	int		stop_heredoc;
	int		cmd_count;
	int		i;
	int		export_flag;
}	t_data;

extern int	g_signal_exit_status;

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
# define REDIRECTION 13

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define IS_DIR 126
# define NOT_DIR 127

//builtsin functions
void	ft_builtins_parent(t_data *data, t_cmd *cmd_list);
void	ft_builtins_child(t_data *data, t_cmd *cmd_list);
void	ft_clean_executed_commands(t_data *data, t_cmd *cmd_list);
void	ft_clean_executed_command(t_data *data, t_cmd *cmd_list);
int		ft_cmd_delete_prev(t_cmd **cmd_list, t_cmd *next_cmd);
//cd functions
void	ft_mini_cd(t_data *data, t_cmd *cmd_list);
char	*ft_normalize_path(t_data *data, char *str);
char	*ft_get_directory(t_data *data, char *comp);
char	*ft_new_path(t_data *data, char **paths, char *new_path, int len);
int		ft_check_if_root(char *str);
int		ft_check_if_current(char *str);
char	*ft_path_back(char *str);
void	ft_change_path(t_data *data, char *new_path);
char	*ft_change_variables(t_data *data, char *line, int i, int j);
void	ft_chdir(t_data *data, char *path, char *str);
int		ft_getenv(t_data *data, char *key);
void	ft_set_paths(t_data *data, char *new_path);
void	ft_addenv(t_data *data, char *key, char *value);
void	ft_update_env(t_data *data, char *key, char *value);
//echo functions
void	ft_mini_echo(t_data *data, t_cmd *cmd_list);
void	ft_print_echo(t_data *data, t_lexer *lexer_list, int flag);
t_lexer	*ft_check_n(t_lexer *lexer_list, int *flag);
void	ft_qsort(char **array);
void	ft_print_env(char **array, int i, int j);
//env functions
void	ft_mini_env(t_data *data, t_cmd *cmd_list);
void	ft_print_environment_variables(t_data *data);
//exit functions
void	ft_mini_exit(t_data *data, t_cmd *cmd_list);
//export functions
void	ft_mini_export(t_data *data, t_cmd *cmd_list, int flag);
int		ft_check_variables(t_data *data, t_lexer *lexer_list);
int		ft_check_equal_counter(char *str);
void	ft_add_env(t_data *data, char **str, int counter);
int		ft_check_ifin_env(t_data *data, char *str);
int		ft_check_valid_variables(t_data *data, char **str);
char	*modify_variable(t_data *data, char *var, char *comp, int *flag);
int		split_string(char *str, char **var, char **comp, int *flag);
int		ft_check_exp_dot(char *str, char **var, int i, int *flag);
int		validate_variable_name(char *var, char *comp);
void	ft_export_case(char *str, char **env_new, int len, int i);
void	ft_dot_case(char *str, int i, char **var);
//pwd function
void	ft_mini_pwd(t_data *data, t_cmd *cmd_list);
//unset function
void	ft_mini_unset(t_data *data, t_cmd *cmd_list, int flag);
//error functions
void	ft_error_export(t_data *data, char *str, int flag);
void	ft_error_cmd(char *str, t_data *data);
void	ft_error_exit(char *str, t_data *data);
void	ft_error(char *str, t_data *data);
void	ft_perror(char *str, int fd);
void	ft_error_exit_numeric(char *str, t_data *data);
void	ft_error_cd(char *str, t_data *data, int flag);
void	ft_exit_normal(t_data *data, t_lexer *lexer_list);
void	ft_error_pwd(t_data *data, char *str);
void	ft_error_unset(t_data *data, char *str, int flag);
void	ft_error_env(t_data *data, char *str);
int		ft_error_double_token(t_data *data, int token);
void	ft_error_dir(t_data *data, char *comp, int type);
//executor functions
int		ft_count_commands(t_cmd *cmd);
void	ft_check_if_heredoc(t_data *data);
t_cmd	*ft_check_if_heredoc_alone(t_cmd *cmd_list);
int		ft_is_dollar(char *str, int c);
pid_t	*ft_allocate_pids(int cmd_count);
void	ft_process_command(t_data *data, t_cmd *current_cmd,
			pid_t *pid, int *pipefds);
void	ft_executor(t_data *data, t_cmd *cmd_list);
void	ft_prepare_executor(t_data *data);
void	ft_here_doc(t_data *data, char *limiter);
void	ft_exec(t_data *data, t_cmd *cmd_list);
void	ft_execute_command(t_data *data, t_cmd *cmd,
			int *input_file, int *pipe_fds);
void	apply_output_redirection(int *output_fds, int output_redir);
void	apply_input_redirection(int *input_fds, int input_redir);
void	ft_handle_redirections(t_cmd *cmd);
void	ft_setup_pipe(int pipefd[2]);
void	initialize_file_descriptors(int *input_fds, int *output_fds,
			int max_files);
void	ft_open_input_files(t_cmd *cmd, int *input_fds);
void	ft_open_output_files(t_cmd *cmd, int *output_fds);
void	prepare_file_descriptors(t_data *data, int *input_fds, int *output_fds);
void	close_file_descriptors(int *input_fds, int *output_fds, int max_files);
pid_t	ft_getpid(void);
t_cmd	*ft_special_cases(t_data *data, t_cmd *cmd_list);
void	ft_check_input_pipe(t_cmd *current_cmd, int pipefd, int *input_fd);
void	apply_output_redirection(int *output_fds, int output_redir);
void	ft_clean_unlink(t_cmd *cmd_list);
t_cmd	*ft_check_exit_special(t_data *data, t_cmd *current_cmd);
void	ft_check_exit(t_data *data, t_cmd *current_cmd);
pid_t	ft_fork_process(void);
int		*ft_initialize_pipefds(int cmd_count);
void	ft_wait_for_children(t_data *data, pid_t *pid, int cmd_count);
//expander functions
void	ft_expander(t_data *data);
//parser functions
int		ft_parser(t_data *data);
int		ft_handle_pipe_error(t_data *data, t_lexer *lexer_list);
void	ft_cmd_add_back(t_cmd **cmd_list, t_cmd *new_cmd);
int		ft_count_args(t_lexer *lexer_list);
void	ft_count_pipes(t_data *data);
t_cmd	*ft_cmd_new(void);
t_lexer	*ft_fill_cmd(t_data *data, t_lexer *lexer_list, t_cmd *cmd_list, int i);
char	**ft_get_commands(t_cmd *cmd_list, int i);
int		ft_get_commands_len(t_cmd *cmd_list);
void	ft_parse_cmd(t_data *data, t_cmd *cmd_list);
void	ft_cmd_clear_list(t_cmd **cmd_list);
char	*find_command_in_paths(t_data *data, char *str);
void	set_lexer_token(t_lexer *lexer_list, char *path);
//lexer functions
size_t	ft_lexer_len(t_lexer *lexer_list);
int		ft_lexer_add(char *readline, int type, t_lexer **lexer_list);
void	ft_lexer_add_back(t_lexer **lexer_list, t_lexer *new_lexer);
t_lexer	*ft_lexer_new(char *readline, int type);
int		ft_lexer_reader(t_data *data);
int		ft_read_words(char *readline, int index, t_lexer **lexer_list);
void	ft_lexer_clear_list(t_lexer **lexer_list);
void	ft_lexer_del_first(t_lexer **lexer_list);
t_lexer	*ft_lexer_clear_one(t_lexer **lexer_list);
void	ft_lexer_del_one(t_lexer **lexer_list, int key);
int		ft_handle_token(t_data *data, int index, t_lexer **lexer_list);
int		ft_check_token(int c);
void	ft_rotate_list_to_node(t_lexer **head, t_lexer *target_node);
//utils
char	*ft_process_withbackslash(char *tmp, int *i, int *j, char *new);
void	ft_check_equal_sign(t_data *data, int i, int counter);
int		ft_no_cmd_after(t_data *data, int flag);
void	ft_export_exit_change(t_data *data);
int		ft_check_if_exit_env(t_data *data, char *var, char *comp);
void	update_envp_variable(char *search_key, char *new_value, char **envp);
void	ft_check_explanation(t_data *data);
void	ft_check_if_empty(t_data *data);
int		ft_check_is_directory(char *str, t_data *data);
int		ft_check_is_file(char *str);
void	ft_check_after_dir(t_data *data);
void	ft_check_quotes_in_string(t_data *data);
char	*ft_process_quotes(char *tmp, t_env *env_list, int i, int j);
char	*ft_process_quotes_in_double(char *tmp, t_env *env_list, int i, int j);
char	*append_and_free(char *old_str, char *new_str);
char	*handle_dollar_sign(char *tmp, t_env *env_list, int *i, int *j);
char	*handle_string(char *tmp, int *i, int *j);
char	*handle_double_quotes(char *tmp, t_env *env_list, int *i, int *j);
char	*handle_single_quotes(char *tmp, int *i, int *j);
char	*ft_process_variable(char *tmp, t_env *env_list, int *i);
char	*ft_get_var(char *str, t_env *env_list);
int		ft_check_token_start_end(char *line);
int		ft_count_quotes(char *line);
int		ft_find_matching_quote(char *line, int index, int *count, int type);
char	*ft_get_shlvl(char *str);
void	ft_add_env_list(char *str, t_env **env_list);
void	ft_env_add_back(t_env **env_list, t_env *new_env);
t_env	*ft_env_new(char *str);
void	ft_env_clear_list(t_env **env_list);
int		ft_find_path(t_data *data);
char	*ft_get_path(char **envp);
void	ft_find_pwd(t_data *data);
void	ft_free_data(t_data *data);
void	ft_initialize_data(t_data *data);
void	ft_implement_data(t_data *data);
void	ft_init(t_data *data, char **envp);
int		ft_readline(t_data *data);
char	*get_readline(t_data *data);
void	ft_trim_readline(t_data *data);
int		ft_skip_spaces(char *str, int i);
int		is_whitespace(char c);
void	ft_swap_strings(char **a, char **b);
int		ft_no_cmd_after(t_data *data, int flag);
int		ft_strcmp_mini(const char *str1, const char *str2);
int		ft_is_char(char *str, char c);
char	**ft_lexer_arrdup(t_lexer *lexer_list);
char	**ft_arrdup(char **arr);
void	ft_arrdup_modified(t_data *data, char **arr, char *str);
void	ft_free_arr(char **arr);
int		ft_arr_len(char **arr);
void	ft_putstr_modified_fd(char *str, int fd);
char	*ft_strjoin_modified(char *s1, char const *s2);
char	*ft_strjoin_modifiedd(char *s1, char *s2);
char	*ft_strjoin_modifiedsd(char *s1, char *s2);
char	*ft_strdup_modified(char *old, char *new);
void	ft_add_arr(t_cmd *cmd_list, char **arr, char *new_item, int flag);
void	ft_free_four(char *s1, char *s2, char *s3, char *s4);
void	ft_reset_data(t_data *data);
void	ft_minishell_loop(t_data *data);
void	print_data(t_data *data);
char	**ft_check_if_question(char **envp);
void	ft_check_heredoc_name(t_data *data);
void	ft_env_update(t_data *data);
void	ft_check_token_lexer(t_data *data);
//signal functions
void	ft_init_signal(void);
void	ft_clear_signal(void);
void	ft_sigint_handler(int sig);
void	ft_sigquit_handler(int sig);
void	ft_signal_incmd(void);
void	ft_reset_signal(void);
void	ft_check_signal(t_data *data);
void	ft_sigint_handler_beforecmd(int sig);
void	ft_signal_inheredoc(t_data *data, pid_t pid);
void	ft_check_export(t_data *data);

#endif
