/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:17:03 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/30 01:10:34 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_signal	g_signal;
void	ft_minishell_loop(t_data *data);
// char *ft_process_dollar_signs(char *tmp, t_env *env_list, int i, int j);

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

static char	*ft_find_env_var(char *str, t_env *env_list, int *len)
{
	while (env_list)
	{
		if (!ft_strncmp(str, env_list->env_var, ft_strlen(env_list->env_var)))
		{
			*len = ft_strlen(env_list->env_var);
			return (env_list->env_comp);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

char *remove_quotes(char *str)
{
    int len = strlen(str);
    if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len - 1] == '\'')))
    {
        char *new_str = ft_substr(str, 1, len - 2); // Create a new substring without the outer quotes
        char *result = remove_quotes(new_str); // Recursively remove quotes
        free(new_str); // Free the intermediate string
        return result;
    }
    return strdup(str); // Return a duplicate of str if no quotes
}

char *ft_strjoin_arr(char **arr, char c)
{
	int i = -1;
	int len = 0;
	while (arr[++i])
		len += strlen(arr[i]);
	char *new = malloc(len + i + 1);
	i = -1;
	int j = 0;
	while (arr[++i])
	{
		strcpy(&new[j], arr[i]);
		j += strlen(arr[i]);
		new[j++] = c;
	}
	new[j - 1] = '\0';
	return new;
}

char *ft_replace_substr(char *str, char *substr, int start, int len)
{
	int new_len = strlen(str) - len + strlen(substr) + 1;
	char *new_str = malloc(new_len + 1);
	strncpy(new_str, str, start);
	strcpy(&new_str[start], substr);
	strcpy(&new_str[start + strlen(substr)], str + start + len);
	new_str[new_len] = '\0';
	return new_str;
}

void ft_replace_variables(char **str, t_env *env_list)
{
    char *env_var;
    char *new_str;
    int i = 0;
    int var_len = 0;

    while ((*str)[i])
    {
        if ((*str)[i] == '$')
        {
            env_var = ft_find_env_var(&(*str)[i], env_list, &var_len);
            if (env_var)
            {
                new_str = ft_replace_substr(*str, env_var, i, var_len);
                free(*str);
                *str = new_str;
                i += strlen(env_var) - 1;
            }
        }
        i++;
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

void ft_replace_value(t_lexer *lexer_list, t_env *env_list)
{
    t_lexer *current_lexer = lexer_list;
    while (current_lexer)
    {
        ft_replace_variables(&(current_lexer->lexer_comp), env_list);
        current_lexer = current_lexer->next;
    }
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
	if (!ft_count_quotes(data->readline))
		return (ft_error("unable to find the next quote\n", data));
	if (!ft_lexer_reader(data))
		return (ft_error("memory error: unable to assign memory\n", data));
	ft_replace_value(data->lexer_list, data->env_list);
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
