/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes_in_string_main_utils.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:21:53 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 08:55:46 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_var(char *str, t_env *env_list)
{
	t_env	*env_var;

	env_var = NULL;
	while (env_list)
	{
		if (!ft_strcmp(str, env_list->env_var))
		{
			env_var = env_list;
			break ;
		}
		env_list = env_list->next;
	}
	free(str);
	if (env_var)
		return (ft_strdup(env_var->env_comp));
	return (ft_strdup(""));
}

char	*ft_process_variable(char *tmp, t_env *env_list, int *i)
{
	int		j;
	char	*var_name;
	char	*value;

	j = 1;
	var_name = NULL;
	while (tmp[*i + j] != '\0' && !is_whitespace(tmp[*i + j])
		&& tmp[*i + j] != 61 && tmp[*i + j] != 37
		&& tmp[*i + j] != '$' && tmp[*i + j] != 34 && tmp[*i + j] != 39
		&& tmp[*i + j] != '/' && tmp[*i + j] != 43 && tmp[*i + j] != 58)
		j++;
	if (tmp[*i + j] == '$' && tmp[*i + j] != '\0' && j == 1)
		j++;
	else if (tmp[*i + j] != '\0' && j == 1)
	{
		value = ft_strdup("$");
		return (value);
	}
	var_name = ft_substr(tmp, *i, j);
	value = ft_get_var(var_name, env_list);
	*i += j;
	if (tmp[*i] == '$' || tmp[*i] == 34 || tmp[*i] == 39 || tmp[*i] == 37
		|| tmp[*i] == '/' || tmp[*i] == 43 || tmp[*i] == 58 || tmp[*i] == 61)
		(*i)--;
	return (value);
}

char	*handle_single_quotes(char *tmp, int *i, int *j)
{
	int		count;
	char	*prefix;
	char	*new;

	count = 0;
	*j += ft_find_matching_quote(tmp, *i, &count, 39);
	if (count % 2 == 0)
	{
		prefix = ft_substr(tmp, *i + 1, *j - 1);
		new = ft_strdup(prefix);
		free(prefix);
		*i += *j;
		*j = 0;
		if (tmp[*i] != '\0')
			(*i)++;
		return (new);
	}
	if (tmp[*i] != '\0')
		(*i)++;
	return (tmp);
}

char	*handle_double_quotes(char *tmp, t_env *env_list, int *i, int *j)
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
		new_withquote = ft_process_quotes_in_double(prefix, env_list, 0, 0);
		new = ft_strdup(new_withquote);
		free(new_withquote);
		free(prefix);
		*i += *j;
		*j = 0;
	}
	else
		new = ft_strdup("");
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
	if (tmp[*i + *j] == 34 || tmp[*i + *j] == 39)
		(*j)--;
	*i += *j;
	if (tmp[*i] != '\0')
		(*i)++;
	return (new);
}
