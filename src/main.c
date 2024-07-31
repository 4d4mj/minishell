/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:17:03 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/31 03:24:01 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_signal	g_signal;
void	ft_minishell_loop(t_data *data);
void	ft_check_after_dir(t_data *data);
void	ft_replace_variables(char **str, t_env *env_list, int i);

void	ft_reset_data(t_data *data)
{
	ft_free_data(data);
	ft_initialize_data(data);
	ft_minishell_loop(data);
}

void	update_envp_variable(char *search_key, char *new_value, char **envp)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(search_key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(search_key, envp[i], key_len))
		{
			free(envp[i]);
			envp[i] = ft_strdup(new_value);
		}
		i++;
	}
}

void	ft_check_if_exit_env(t_data *data, char *var, char *comp, char *new)
{
	char	*search_key;
	char	*env_key;
	t_env	*env_list;

	env_list = data->env_list;
	search_key = ft_strjoin("$", var);
	env_key = ft_strjoin(var, "=");
	while (env_list)
	{
		if (!ft_strcmp(search_key, env_list->env_var))
		{
			free(data->env_list->env_comp);
			data->env_list->env_comp = ft_strdup(comp);
			update_envp_variable(env_key, new, data->envp);
		}
		env_list = env_list->next;
	}
	free(var);
	free(comp);
	free(search_key);
	free(env_key);
}

void	ft_export_exit_change(t_data *data)
{
	t_lexer	*lexer_list;
	char	*var;
	char	*comp;
	int		i;

	lexer_list = data->lexer_list;
	while (lexer_list)
	{
		i = 0;
		if (lexer_list->lexer_comp[i] == '=')
			;
		else
		{
			while (lexer_list->lexer_comp[i] != '\0'
				&& lexer_list->lexer_comp[i] != '=')
				i++;
			if (lexer_list->lexer_comp[i] == '\0')
				break ;
			var = ft_substr(lexer_list->lexer_comp, 0, i);
			comp = ft_substr(lexer_list->lexer_comp, i + 1, ft_strlen(lexer_list->lexer_comp) - i);
			ft_check_if_exit_env(data, var, comp, lexer_list->lexer_comp);
		}
		ft_lexer_del_first(&data->lexer_list);
		lexer_list = data->lexer_list;
	}
}

int	ft_no_cmd_after(t_data *data, int flag, int i)
{
	t_lexer	*lexer_list;

	lexer_list = data->lexer_list;
	while (lexer_list && lexer_list->token != PIPE)
	{
		i = 0;
		while (lexer_list->lexer_comp && lexer_list->lexer_comp[i])
		{
			if (lexer_list->lexer_comp[i] == '=')
				break ;
			i++;
		}
		if (lexer_list->lexer_comp && lexer_list->lexer_comp[i] == '\0')
		{
			break ;
		}
		flag++;
		lexer_list = lexer_list->next;
	}
	if (lexer_list)
	{
		while (flag-- > 0)
			ft_lexer_del_first(&data->lexer_list);
	}
	return (flag);
}

void	ft_check_equal_sign(t_data *data, int i, int counter)
{
	char	*line;

	if (ft_no_cmd_after(data, 0, 0))
	{
		line = data->lexer_list->lexer_comp;
		if (line && ft_isalpha(line[0]))
		{
			while (line[++i])
			{
				if (line [i + 1] && line[i] == '=' && line[i + 1] != '=')
					counter++;
				else if (line[i + 1] && line[i] == '=' && line[i + 1] == '=')
				{
					counter = 0;
					break ;
				}
				else if (line[i + 1] == '\0' && line[i - 1] != '='
					&& line[i] == '=')
					counter++;
			}
			if (counter > 0)
				ft_export_exit_change(data);
		}
	}
}

void	ft_check_explanation(t_data *data)
{
	char	*readline;
	t_lexer	*lexer_list;

	lexer_list = data->lexer_list;
	readline = data->lexer_list->lexer_comp;
	if (readline && readline[0] == '!' && readline[1] == '\0')
	{
		if (readline[1] == '\0' && lexer_list->next == NULL)
		{
			g_signal.exit_status = EXIT_FAILURE;
			ft_reset_data(data);
		}
		data->explantion = 1;
		ft_lexer_del_first(&data->lexer_list);
	}
	ft_check_equal_sign(data, 0, 0);
	if (!data->lexer_list)
		ft_reset_data(data);
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

int	ft_check_is_directory(char *str, t_data *data)
{
	int			flag;
	struct stat	path_stat;

	flag = 0;
	if (str && str[0] == '/')
	{
		flag = 1;
		if (stat(str, &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
				ft_error_dir(data, str, IS_DIR);
			else
				ft_error_dir(data, str, NOT_DIR);
		}
		else
			perror("stat");
	}
	return (flag);
}

void	ft_check_if_empty(t_data *data)
{
	if ((data->readline[0] == ':') && (data->readline[1] == '\0'
			|| is_whitespace(data->readline[1])))
		return (ft_reset_data(data));
	if (data->readline[0] == '.')
	{
		if (data->readline[1] == '\0')
		{
			ft_putstr_fd("minishell: .: filename argument required\n",
				STDERR_FILENO);
			g_signal.exit_status = 2;
			ft_reset_data(data);
		}
		else if (data->readline[1] == '.' && data->readline[2] == '\0')
			ft_error_cmd("..", data);
	}
}

void	ft_check_after_dir(t_data *data)
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

static char	*ft_find_env_var(char *str, int *len)
{
	int	i;

	i = 1;
	while (ft_isalnum(str[i]))
		i++;
	*len = i;
	return (getenv(ft_substr(str, 1, i - 1)));
	if (!ft_strncmp(str, "$UID", i))
	{
		*len = 4;
		return (ft_strdup("1000"));
	}
	return (NULL);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*new_str;
	char	*result;
	int		flag;
	char	quote_char;

	len = ft_strlen(str);
	printf("str = %s\n", str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\'')))
	{
		if (ft_in('\'', str) && ft_in('"', str))
			flag = 1;
		else
			flag = 0;
		quote_char = str[0];
		new_str = ft_substr(str, 1, len - 2);
		result = remove_quotes(new_str);
		free(new_str);
		if (flag)
		{
			new_str = (char *)malloc(ft_strlen(result) + 3);
			if (!new_str)
				return (NULL);
			new_str[0] = quote_char;
			ft_strcpy(new_str + 1, result);
			new_str[ft_strlen(result) + 1] = quote_char;
			new_str[ft_strlen(result) + 2] = '\0';
			free(result);
			return (new_str);
		}
		return (result);
	}
	return (ft_strdup(str));
}

char *ft_strjoin_arr(char **arr, char c)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	len = 0;
	i = -1;
	while (arr[++i])
		len += strlen(arr[i]);
	new = malloc(len + i + 1);
	i = -1;
	j = 0;
	while (arr[++i])
	{
		strcpy(&new[j], arr[i]);
		j += strlen(arr[i]);
		new[j++] = c;
	}
	new[j - 1] = '\0';
	return (new);
}

char	*ft_replace_substr(char *str, char *substr, int start, int len)
{
	int		new_len;
	char	*new_str;

	new_len = strlen(str) - len + strlen(substr) + 1;
	new_str = malloc(new_len + 1);
	strncpy(new_str, str, start);
	strcpy(&new_str[start], substr);
	strcpy(&new_str[start + strlen(substr)], str + start + len);
	new_str[new_len] = '\0';
	return (new_str);
}

char *remove_wrong_variable(char *str, t_env *env_list, int i)
{
	char	*new_str;
	int		len;
	int		flag;

	len = 0;
	flag = 0;
	while (str[i] && str[i] != '$' && str[i] != '\\')
		i++;
	if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '"'))
	{
		new_str = ft_replace_substr(str, "", i, 1);
	}
	else if (ft_isalnum(str[i + 1]))
	{
		while ((str[len + i] == '$' || ft_isalnum(str[len + i])) && flag < 2)
		{
			len++;
			if (str[len + i] == '$' || str[len + i] == '\\')
				flag++;
		}
		new_str = ft_replace_substr(str, "", i, len);
		free(str);
	}
	else
		new_str = ft_strdup(str);
	ft_replace_variables(&new_str, env_list, -1);
	return (new_str);
}

void	ft_replace_variables(char **str, t_env *env_list, int i)
{
	char	*env_var;
	char	*new_str;
	int		var_len;

	var_len = 0;
	if (!str || !*str)
		return ;
	if (((*str)[0] == '\'' && (*str)[strlen(*str) - 1] == '\''
		&& ft_in('\'', *str) == 2 && !ft_in('"', *str)) || ft_strlen(*str) == 1)
		return ;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			if (i && (*str)[i - 1] == '\\')
				continue ;
			env_var = getenv(&(*str)[i + 1]);
			env_var = ft_find_env_var(&(*str)[i], &var_len);
			if (env_var)
			{
				new_str = ft_replace_substr(*str, env_var, i, var_len);
				free(*str);
				*str = new_str;
				i += strlen(env_var) - 1;
			}
			else
				*str = remove_wrong_variable(*str, env_list, i);
		}
	}
}

char	*get_readline(t_data *data)
{
	char	*str;
	char	*tmp;

	str = ft_strdup(data->pwd);
	if (!ft_strncmp(data->pwd, data->home, ft_strlen(data->home)))
	{
		tmp = ft_strjoin("~", &data->pwd[ft_strlen(data->home)]);
		free(str);
		str = tmp;
	}
	tmp = ft_strjoin("\033[1;32mminishell:\033[1;34m", str);
	str = ft_strjoin(tmp, "\033[0m$ ");
	free(tmp);
	return (str);
}

void	ft_replace_value(t_lexer *lexer_list, t_env *env_list)
{
	t_lexer	*current_lexer;

	current_lexer = lexer_list;
	while (current_lexer)
	{
		ft_replace_variables(&(current_lexer->lexer_comp), env_list, -1);
		current_lexer = current_lexer->next;
	}
}

// static t_env	*ft_find_env_var(char *str, t_env *env_list)
// {
// 	while (env_list)
// 	{
// 		if (!ft_strcmp(str, env_list->env_var))
// 			return (env_list);
// 		env_list = env_list->next;
// 	}
// 	return (NULL);
// }

// char *ft_get_var(char *str, t_env *env_list)
// {
// 	t_env	*env_var;

// 	env_var = ft_find_env_var(str, env_list);
// 	free(str);
// 	if (env_var)
// 	{
// 		return (ft_strdup(env_var->env_comp));
// 	}
// 	return (ft_strdup(" "));
// }

// char	*ft_process_variable(char *tmp, t_env *env_list, int *i)
// {
// 	int		j;
// 	char	*var_name;
// 	char	*value;
// 	char	*new;

// 	j = 1;
// 	var_name = NULL;
// 	while (tmp[*i + j] != '\0' && !is_whitespace(tmp[*i + j]) && tmp[*i + j] != '$')
// 		j++;
// 	var_name = ft_substr(tmp, *i, j);
// 	value = ft_get_var(var_name, env_list);
// 	new = ft_strjoin_modified(NULL, value);
// 	free(value);
// 	*i += j;
// 	return (new);
// }
// static char	*handle_single_quotes(char *tmp, int *i, int *j)
// {
// 	int		count;
// 	char	*prefix;
// 	char	*new;

// 	count = 0;
// 	*j += ft_find_matching_quote(tmp, *i, &count, 39);
// 	if (count % 2 == 0)
// 	{
// 		prefix = ft_substr(tmp, *i, *j + 1);
// 		new = ft_strdup(prefix);
// 		free(prefix);
// 		*i += *j;
// 		*j = 0;
// 		return (new);
// 	}
// 	return (tmp);
// }

// static char *handle_double_quotes(char *tmp, t_env *env_list, int *i, int *j)
// {
// 	int		count;
// 	char	*prefix;
// 	char	*new;
// 	//char	*new_withquote;
//  (void) env_list;
// 	count = 0;
// 	*j += ft_find_matching_quote(tmp, *i, &count, 34);
// 	if (count % 2 == 0)
// 	{
// 		prefix = ft_substr(tmp, *i + 1, *j - 1);
// 		// new_withquote = ft_process_dollar_signs(prefix, env_list, 0, 0);
// 		new = ft_strdup(prefix);
// 		// free(new_withquote);
// 		free(prefix);
// 		*i += *j;
// 		*j = 0;
// 		if (tmp[*i] != '\0')
// 			(*i)++;
// 	}
// 	else
// 	{
// 		new = ft_strdup("");
// 	}
// 	return (new);
// }

// static char *handle_dollar_sign(char *tmp, t_env *env_list, int *i, int *j)
// 	{
// 	char	*prefix;
// 	char	*variable_result;
// 	char	*new;
// 	char	*new_with_variable;

// 	prefix = ft_substr(tmp, *i, *j);
// 	new = ft_strdup(prefix);
// 	free(prefix);
// 	*i += *j;
// 	*j = 0;
// 	if (tmp[*i] == '$')
// 	{
// 		variable_result = ft_process_variable(tmp, env_list, i);
// 		new_with_variable = ft_strjoin_modified(new, variable_result);
// 		new = new_with_variable;
// 		free(variable_result);
// 	}
// 	if (tmp[*i] != '\0')
// 		(*i)++;
// 	return (new);
// }

// char	*handle_string(char *tmp, int *i, int *j)
// {
// 	char	*prefix;
// 	char	*new;

// 	prefix = ft_substr(tmp, *i, *j);
// 	new = ft_strdup(prefix);
// 	free(prefix);
// 	*i += *j;
// 	*j = 0;
// 	if (tmp[*i] != '\0')
// 		(*i)++;
// 	return (new);
// }
// static char *append_and_free(char *old_str, char *new_str)
// {
// 	char	*result;

// 	if (old_str == NULL)
// 		result = ft_strdup(new_str);
// 	else
// 		result = ft_strjoin_modified(old_str, new_str);
// 	free(new_str);
// 	return (result);
// }

// char *ft_process_quotes(char *tmp, t_env *env_list, int i, int j)
// {
// 	char	*new;
// 	char	*result;

// 	new = ft_strdup("");
// 	while (tmp && tmp[i] != '\0')
// 	{
// 		j = 0;
// 		result = NULL;
// 		while (tmp[i + j] != '\0' && tmp[i + j] != '$'
// 			&& tmp[i + j] != 34 && tmp[i + j] != 39)
// 			j++;
// 		if (tmp[i + j] == 39)
// 			result = handle_single_quotes(tmp, &i, &j);
// 		else if (tmp[i + j] == 34)
// 			result = handle_double_quotes(tmp, env_list, &i, &j);
// 		else if (tmp[i + j] == '\0')
// 			result = handle_string(tmp, &i, &j);
// 		if (result)
// 			new = append_and_free(new, result);
// 		if (tmp[i] != '\0')
// 			i++;
// 	}
// 	return (new);
// }

// void	ft_check_quotes_in_string(t_data *data)
// {
// 	t_lexer	*current_lexer;
// 	char	*tmp;
// 	char	*new;

// 	current_lexer = data->lexer_list;
// 	while (current_lexer)
// 	{
// 		tmp = ft_strdup(current_lexer->lexer_comp);
// 		new = ft_process_quotes(tmp, data->env_list, 0, 0);
// 		free(tmp);
// 		free(current_lexer->lexer_comp);
// 		current_lexer->lexer_comp = new;
// 		current_lexer = current_lexer->next;
// 	}
// }
void	ft_minishell_loop(t_data *data)
{
	int		token;
	char	*str;

	ft_expander(data);
	str = get_readline(data);
	data->readline = readline(str);
	if (data->readline[0] == '\0')
		return (ft_reset_data(data));
	add_history(data->readline);
	free(str);
	ft_trim_readline(data);
	if (!ft_count_quotes(data->readline))
		return (ft_error("unable to find the next quote\n", data));
	if (!ft_lexer_reader(data))
		return (ft_error("memory error: unable to assign memory\n", data));
	ft_replace_value(data->lexer_list, data->env_list);
	// ft_check_quotes_in_string(data);
	ft_check_explanation(data);
	ft_check_if_empty(data);
	if (!ft_check_is_directory(data->lexer_list->lexer_comp, data))
	{
		token = ft_check_token_start_end(data->readline);
		if (token)
			ft_error_double_token(data, token);
		ft_parser(data);
		ft_prepare_executor(data);
	}
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
