/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:26:38 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/29 14:12:37 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_question_variable(char *variable, char **env)
{
	char	*first_part;
	int		i;

	i = 0;
	first_part = NULL;
	while (env[i])
	{
		if (variable[0] == env[i][0])
			break ;
		i++;
	}
	first_part = ft_substr(env[i], 2, ft_strlen(env[i]) - 2);
	ft_putstr_fd(first_part, STDOUT_FILENO);
	free(first_part);
}

void	ft_handle_general_variable(char *variable, char **env)
{
	char	*first_part;
	int		i;

	i = 0;
	first_part = NULL;
	while (env[i])
	{
		if (!ft_strncmp(variable, env[i], ft_strlen(variable)))
			break ;
		i++;
	}
	if (env[i] && env[i][ft_strlen(variable)] == '=')
	{
		first_part = ft_substr(env[i], ft_strlen(variable) + 1,
				ft_strlen(env[i]) - ft_strlen(variable) - 1);
	}
	if (first_part)
		ft_putstr_fd(first_part, STDOUT_FILENO);
	free(first_part);
}

void	ft_get_variable(char *variable, char **env)
{
	if (variable[0] == '?')
	{
		ft_handle_question_variable(variable, env);
		free(variable);
	}
	else
	{
		ft_handle_general_variable(variable, env);
		free(variable);
	}
}

void	ft_print_expander(t_data *data, char *str, int flag)
{
	t_lexer	*new_lexer;

	if (flag)
	{
		new_lexer = ft_lexer_new(ft_strdup("-n"), ARG);
		if (!new_lexer)
			return ;
		if (!ft_lexer_add(str, ARG, &new_lexer))
			return ;
	}
	else
	{
		new_lexer = ft_lexer_new(str, ARG);
		if (!new_lexer)
			return ;
	}
	ft_print_echo(data, new_lexer, 0);
	ft_lexer_clear_list(&new_lexer);
}

char	*ft_check_quote_string(char *str)
{
	char	*tmp;

	if (str[0] == 34 || str[0] == 39)
	{
		tmp = ft_substr(str, 1, ft_strlen(str) - 2);
		free (str);
		return (tmp);
	}
	return (str);
}

char	*ft_parse_variable(char **variable, t_lexer *list, char *str, t_data *data)
{
	int		i;
	char	*tmp;

(void) data;
	i = -1;
	while (variable[++i])
	{
		if (i != 0)
			str = ft_strjoin_modified(str, " ");
		if (variable[i][0] == '$' && variable[i][1] != '\0')
		{
			tmp =NULL;
			//tmp = ft_get_variable(variable[i], data->envp);
			str = ft_strjoin_modified(str, tmp);
			if (tmp)
				free(tmp);
		}
		else
			str = ft_strjoin_modified(str, variable[i]);
	}
	if (list->next)
	{
		str = ft_strjoin_modified(str, " ");
	}
	return (str);
}

void	ft_expander_echo(t_data *data, t_cmd *cmd_list, int flag)
{
	t_lexer	*lexer_list;
	char	**variableiable;
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	lexer_list = cmd_list->lexer_list->next;
	lexer_list = ft_check_n(lexer_list, &flag);
	if (!lexer_list && flag)
		ft_reset_data(data);
	while (lexer_list)
	{
		tmp = ft_check_quote_string(ft_strdup(lexer_list->lexer_comp));
		variableiable = ft_split(tmp, ' ');
		free (tmp);
		str = ft_parse_variable(variableiable, lexer_list, str, data);
		ft_free_arr(variableiable);
		lexer_list = lexer_list->next;
	}
	ft_print_expander(data, str, flag);
}
