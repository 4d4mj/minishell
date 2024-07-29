/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:17:03 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/29 22:35:25 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_signal	g_signal;
void	ft_minishell_loop(t_data *data);
char *ft_process_dollar_signs(char *tmp, t_env *env_list, int i, int j);

void	ft_reset_data(t_data *data)
{
	ft_free_data(data);
	ft_initialize_data(data);
	ft_minishell_loop(data);
}

void	ft_check_equal_sign(t_data *data, int i, int counter)
{
	char	*newreadline;
	char	*readline;

	readline = data->readline;
	if (ft_isalpha(readline[0]))
	{
		while (readline[++i])
		{
			if (readline[i] == '=')
				counter++;
			else if (is_whitespace(readline[i]))
				break ;
		}
		if (counter > 0)
		{
			newreadline = ft_substr(readline, i, ft_strlen(readline) - i);
			if (newreadline[0] == '\0')
			{
				free(newreadline);
				ft_reset_data(data);
			}
			free (readline);
			data->readline = newreadline;
		}
	}
}

void	ft_check_explanation(t_data *data)
{
	char	*newreadline;
	char	*readline;

	readline = data->readline;
	if (readline[0] == '!' && (readline[1] == '\0'
			|| is_whitespace(readline[1])))
	{
		if (readline[1] == '\0')
		{
			g_signal.exit_status = EXIT_FAILURE;
			ft_reset_data(data);
		}
		data->explantion = 1;
		newreadline = ft_substr(readline, 1, ft_strlen(readline) - 1);
		free (readline);
		data->readline = newreadline;
	}
	ft_check_equal_sign(data, 0, 0);
}

void	ft_trim_readline(t_data *data)
{
	char	*tmp;

	tmp = ft_strtrim(data->readline, " ");
	if (data->readline)
		free(data->readline);
	data->readline = tmp;
	if (!data->readline)
	{
		ft_error_exit ("exit", data);
		exit(EXIT_SUCCESS);
	}
}

int	ft_check_token_start_end(char *line)
{
	int	len;
	int	type_e;

	type_e = 0;
	len = ft_strlen(line) - 1;
	if (len >= 0)
		type_e = ft_check_token(line[len]);
	if ((len && (ft_check_token(line[len - 1]) == TRUNC && type_e == TRUNC)))
		return (APPEND);
	else if ((len && (ft_check_token(line[len - 1]) == INPUT
				&& type_e == INPUT)))
		return (HEREDOC);
	else if (type_e)
		return (type_e);
	return (0);
}

void	ft_check_is_directory(t_data *data, char *str, int i)
{
	if (str[i] == '/' || str[i] == '~')
	{
		if (str[i] == '/')
		{
			while (str[++i])
			{
				if (str[i] == '/' || str[i] == '.')
					;
				else
					break ;
			}
		}
		else
			i++;
		if (str[i] == '\0')
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(" : Is a directory\n", STDERR_FILENO);
			g_signal.exit_status = IS_DIR;
			ft_reset_data(data);
		}
	}
}

void	ft_check_if_empty(t_data *data)
{
	if (data->readline[0] == '\0')
		return (ft_reset_data(data));
	add_history(data->readline);
	if ((data->readline[0] == ':') && (data->readline[1] == '\0'
			|| is_whitespace(data->readline[1])))
		return (ft_reset_data(data));
	if (data->readline[0] == '.')
	{
		if (data->readline[1] == '\0')
		{
			ft_putstr_fd("minishell: .:filename argument required\n",
				STDERR_FILENO);
			g_signal.exit_status = 2;
			ft_reset_data(data);
		}
		else if (data->readline[1] == '.' && data->readline[2] == '\0')
			ft_error_cmd("..", data);
	}
}
void ft_check_after_dir(t_data *data)
{
	int		i;
	char	*new_readline;

	i = 0;
	while (data->readline[i] != '\0' && !is_whitespace(data->readline[i]))
		i++;
	while (data->readline[i] != '\0' && is_whitespace(data->readline[i])
		&& data->readline[i] != '|')
		i++;
	if (data->readline[i] == '\0')
		ft_reset_data(data);
	if (data->readline[i + 1] != '\0' && data->readline[i] == '|')
		i++;
	if (data->readline[i] != '\0')
	{
		new_readline = ft_substr(data->readline, i,
				ft_strlen(data->readline) - i);
		free(data->readline);
		data->readline = new_readline;
	}
	else
		ft_reset_data(data);
}
void ft_error_dir(t_data *data, char *comp, int type)
{
	if (type == IS_DIR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(comp, STDERR_FILENO);
		ft_putstr_fd(" : Is a directory\n", STDERR_FILENO);
		g_signal.exit_status = IS_DIR;
	}
	else if (comp)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putstr_fd(comp, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		g_signal.exit_status = NOT_DIR;
	}
	ft_check_after_dir(data);
}
void	ft_check_is_dollar(t_data *data)
{
	t_env	*cur_env;
	int		len;

	cur_env = data->env_list;
	if (data->readline[0] == '$')
	{
		while (cur_env)
		{
			len = ft_strlen(cur_env->env_var);
			if (!ft_strncmp(cur_env->env_var, data->readline, len)
				&& (data->readline[len] == '\0'
					|| is_whitespace(data->readline[len])))
			{
				if (!ft_strcmp(cur_env->env_var, "$HOME"))
					ft_error_dir(data, cur_env->env_comp, IS_DIR);
				else
					ft_error_dir(data, cur_env->env_comp, NOT_DIR);
			}
			cur_env = cur_env->next;
		}
		if (!cur_env)
			ft_error_dir(data, NULL, NOT_DIR);
	}
}
static t_env	*ft_find_env_var(char *str, t_env *env_list)
{
	while (env_list)
	{
		if (!ft_strcmp(str, env_list->env_var))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

char *ft_get_var(char *str, t_env *env_list)
{
	t_env	*env_var;

	env_var = ft_find_env_var(str, env_list);
	free(str);
	if (env_var)
	{
		return (ft_strdup(env_var->env_comp));
	}
	return (ft_strdup(" "));
}

// static char	*ft_extract_prefix(char *tmp, int *i)
// {
// 	char	*prefix;
// 	char	*new;

// 	prefix = ft_substr(tmp, 0, *i);
// 	new = ft_strjoin_modified(NULL, prefix);
// 	free(prefix);
// 	*i += 1;
// 	return (new);
// }
char	*ft_process_variable(char *tmp, t_env *env_list, int *i)
{
	int		j;
	char	*var_name;
	char	*value;
	char	*new;

	j = 1;
	var_name = NULL;
	while (tmp[*i + j] != '\0' && !is_whitespace(tmp[*i + j]) && tmp[*i + j] != '$')
		j++;
	var_name = ft_substr(tmp, *i, j);
	value = ft_get_var(var_name, env_list);
	new = ft_strjoin_modified(NULL, value);
	free(value);
	*i += j;
	return (new);
}
static char	*handle_single_quotes(char *tmp, int *i, int *j)
{
	int		count;
	char	*prefix;
	char	*new;

	count = 0;
	*j += ft_find_matching_quote(tmp, *i, &count, 39);
	if (count % 2 == 0)
	{
		prefix = ft_substr(tmp, *i, *j + 1);
		new = ft_strdup(prefix);
		free(prefix);
		*i += *j;
		*j = 0;
		return (new);
	}
	return (tmp);
}

static char *handle_double_quotes(char *tmp, t_env *env_list, int *i, int *j)
{
	int		count;
	char	*prefix;
	char	*new;
	char	*new_withquote;

	count = 0;
	*j += ft_find_matching_quote(tmp, *i, &count, 34);
	if (count % 2 == 0)
	{
		prefix = ft_substr(tmp, *i + 1, *j - 1);
		new_withquote = ft_process_dollar_signs(prefix, env_list, 0, 0);
		new = ft_strdup(new_withquote);
		free(new_withquote);
		free(prefix);
		*i += *j;
		*j = 0;
		if (tmp[*i] != '\0')
			(*i)++;
	}
	else
	{
		new = ft_strdup("");
	}
	return (new);
}

static char *handle_dollar_sign(char *tmp, t_env *env_list, int *i, int *j)
	{
	char	*prefix;
	char	*variable_result;
	char	*new;
	char	*new_with_variable;

	prefix = ft_substr(tmp, *i, *j);
	new = ft_strdup(prefix);
	free(prefix);
	*i += *j;
	*j = 0;
	if (tmp[*i] == '$')
	{
		variable_result = ft_process_variable(tmp, env_list, i);
		new_with_variable = ft_strjoin_modified(new, variable_result);
		new = new_with_variable;
		free(variable_result);
	}
	if (tmp[*i] != '\0')
		(*i)++;
	return (new);
}

char	*handle_string(char *tmp, int *i, int *j)
{
	char	*prefix;
	char	*new;

	prefix = ft_substr(tmp, *i, *j);
	new = ft_strdup(prefix);
	free(prefix);
	*i += *j;
	*j = 0;
	if (tmp[*i] != '\0')
		(*i)++;
	return (new);
}
static char *append_and_free(char *old_str, char *new_str)
{
	char	*result;

	if (old_str == NULL)
		result = ft_strdup(new_str);
	else
		result = ft_strjoin_modified(old_str, new_str);
	free(new_str);
	return (result);
}

char *ft_process_dollar_signs(char *tmp, t_env *env_list, int i, int j)
{
	char	*new;
	char	*result;

	new = ft_strdup("");
	while (tmp[i] != '\0')
	{
		j = 0;
		result = NULL;
		while (tmp[i + j] != '\0' && tmp[i + j] != '$'
			&& tmp[i + j] != 34 && tmp[i + j] != 39)
			j++;
		if (tmp[i + j] == 39)
			result = handle_single_quotes(tmp, &i, &j);
		else if (tmp[i + j] == 34)
			result = handle_double_quotes(tmp, env_list, &i, &j);
		else if (tmp[i + j] == '$')
			result = handle_dollar_sign(tmp, env_list, &i, &j);
		else if (tmp[i + j] == '\0')
			result = handle_string(tmp, &i, &j);
		if (result)
			new = append_and_free(new, result);
		if (tmp[i] != '\0')
			i++;
	}
	return (new);
}

void	ft_check_dollar_sign(t_data *data)
{
	t_lexer	*current_lexer;
	char	*tmp;
	char	*new;

	current_lexer = data->lexer_list;
	while (current_lexer)
	{
		tmp = ft_strdup(current_lexer->lexer_comp);
		new = ft_process_dollar_signs(tmp, data->env_list, 0, 0);
		free(tmp);
		free(current_lexer->lexer_comp);
		current_lexer->lexer_comp = new;
		current_lexer = current_lexer->next;
	}
}

char *get_readline(t_data *data)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin("\033[1;32mminishell:\033[1;34m", data->pwd);
	str = ft_strjoin(tmp, "\033[0m$ ");
	free(tmp);
	return (str);
}

void	ft_minishell_loop(t_data *data)
{
	int		token;
	char	*str;

	ft_expander(data);
	str = get_readline(data);
	data->readline = readline(str);
	free(str);
	ft_trim_readline(data);
	ft_check_if_empty(data);
	ft_check_explanation(data);
	ft_check_is_directory(data, data->readline, 0);
	ft_check_is_dollar(data);
	if (!ft_count_quotes(data->readline))
		return (ft_error("unable to find the next quote\n", data));
	if (!ft_lexer_reader(data))
		return (ft_error("memory error: unable to assign memory\n", data));
	ft_check_dollar_sign(data);
	token = ft_check_token_start_end(data->readline);
	if (token)
		ft_error_double_token(data, token);
	ft_parser(data);
	ft_prepare_executor(data);
	ft_reset_data(data);
}

void ft_init(t_data *data, char **envp)
{
	data->readline = NULL;
	data->lexer_list = NULL;
	data->cmd_list = NULL;
	data->env_list = NULL;
	data->envp = NULL;
	data->home = NULL;
	data->pwd = NULL;
	data->old_pwd = NULL;
	data->explantion = 0;
	g_signal.exit_status = 0;
	ft_arrdup_modified(data, envp, "?=0");
	ft_initialize_data(data);
	ft_minishell_loop(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
		ft_error("This program does not accept arguments\n", &data);
	ft_init(&data, envp);
	return (0);
}
