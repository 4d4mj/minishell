/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes_in_string_main.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:15:42 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/21 17:15:01 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_dollar_sign(char *tmp, t_env *env_list, int *i, int *j)
{
	char	*prefix;
	char	*variable_result;
	char	*new;
	char	*new_with_variable;

	if (tmp[*i + *j] && tmp[*i + *j + 1] != '\0'
		&& !is_whitespace(tmp[*i + *j + 1]))
		prefix = ft_substr(tmp, *i, *j);
	else if (tmp[*i + *j + 1] == '\0' || is_whitespace(tmp[*i + *j + 1]))
		prefix = ft_substr(tmp, *i, *j + 1);
	new = ft_strdup(prefix);
	free(prefix);
	*i += *j;
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

char	*append_and_free(char *old_str, char *new_str)
{
	char	*result;

	if (old_str == NULL)
		result = ft_strdup(new_str);
	else
		result = ft_strjoin_modified(old_str, new_str);
	free(new_str);
	return (result);
}

char	*ft_process_quotes_in_double(char *tmp, t_env *env_list, int i, int j)
{
	char	*new;
	char	*result;

	new = ft_strdup("");
	while (tmp && tmp[i] != '\0')
	{
		j = 0;
		result = NULL;
		while (tmp[i + j] != '\0' && tmp[i + j] != '$')
			j++;
		if (tmp[i + j] == '$')
			result = handle_dollar_sign(tmp, env_list, &i, &j);
		else
			result = handle_string(tmp, &i, &j);
		if (result)
			new = append_and_free(new, result);
	}
	return (new);
}

char	*ft_process_quotes(char *tmp, t_env *env_list, int i, int j)
{
	char	*new;
	char	*result;

	new = ft_strdup("");
	while (tmp != NULL && tmp[i] != '\0')
	{
		j = 0;
		result = NULL;
		while (tmp[i + j] != '\0' && tmp[i + j] != '$'
			&& tmp[i + j] != 34 && tmp[i + j] != 39 && tmp[i + j] != '\\')
			j++;
		if (tmp[i + j] == '\\')
			result = ft_process_withbackslash(tmp, &i, &j, NULL);
		else if (tmp[i + j] == '$')
			result = handle_dollar_sign(tmp, env_list, &i, &j);
		else if (tmp[i] != 34 && tmp[i] != 39)
			result = handle_string(tmp, &i, &j);
		else if (tmp[i + j] == 39)
			result = handle_single_quotes(tmp, &i, &j);
		else if (tmp[i + j] == 34)
			result = handle_double_quotes(tmp, env_list, &i, &j);
		if (result)
			new = append_and_free(new, result);
	}
	return (new);
}

void	ft_check_quotes_in_string(t_data *data)
{
	t_lexer	*current_lexer;
	char	*tmp;
	char	*new;

	current_lexer = data->lexer_list;
	while (current_lexer)
	{
		tmp = ft_strdup(current_lexer->lexer_comp);
		new = ft_process_quotes(tmp, data->env_list, 0, 0);
		free(tmp);
		free(current_lexer->lexer_comp);
		current_lexer->lexer_comp = new;
		current_lexer = current_lexer->next;
	}
}
