/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:44:40 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/30 08:57:33 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_lexer_arrdup(t_lexer *lexer_list)
{
	char	**env_variables;
	int		len;

	len = ft_lexer_len(lexer_list);
	env_variables = ft_calloc(sizeof(char *), len + 1);
	if (!env_variables)
		return (NULL);
	len = 0;
	while (lexer_list)
	{
		env_variables[len] = ft_strdup(lexer_list->lexer_comp);
		if (env_variables[len] == NULL)
		{
			ft_free_arr(env_variables);
			return (env_variables);
		}
		lexer_list = lexer_list->next;
		len++;
	}
	return (env_variables);
}

char	*ft_check_quotes(char *str)
{
	char	*new_str;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (str[0] == 34 || str[0] == 39)
	{
		i = ft_find_matching_quote(str, 0, &count, str[0]);
		if (count % 2 == 0)
			new_str = ft_substr(str, 1, i -1);
		return (new_str);
	}
	return (ft_strdup(str));
}

void	ft_add_env(t_data *data, char *str, int counter)
{
	char	**env_new;
	int		len;
	int		i;

	if (counter == 0 || str[0] == '=')
		return ;
	i = -1;
	len = ft_arr_len(data->envp);
	env_new = ft_calloc(sizeof(char *), len + 2);
	if (!env_new)
		return ;
	while (++i < len)
		env_new[i] = ft_strdup(data->envp[i]);
	i = ft_strlen(str) - 1;
	if (str[i] == '=')
		str = ft_strjoin_modified(ft_substr(str, 0, len -1), "''");
	env_new[len] = ft_strdup(str);
	env_new[len + 1] = NULL;
	if (str[i] == '=')
		free(str);
	ft_free_arr(data->envp);
	data->envp = env_new;
}

int	ft_check_variables(t_data *data, char **env_variables, int i, int j)
{
	int		check;
	int		counter;
	char	*str;

	check = 1;
	while (env_variables[i])
	{
		str = ft_check_quotes(env_variables[i]);
		j = 0;
		counter = 0;
		if (str[j] == '=')
			check = 0;
		while (str[++j])
		{
			if (str[j] == '=' && str[j + 1] != '=')
				counter++;
		}
		if (counter == 0)
			check = counter;
		ft_add_env(data, str, counter);
		free(str);
		i++;
	}
	return (check);
}

void	ft_mini_export(t_data *data, t_cmd *cmd_list)
{
	t_lexer	*lexer_list;
	char	**env_variables;
	int		check;

	lexer_list = cmd_list->lexer_list->next;
	if (!lexer_list)
	{
		env_variables = ft_arrdup(data->envp);
		ft_qsort(env_variables);
		ft_free_arr(env_variables);
		return ;
	}
	env_variables = ft_lexer_arrdup(lexer_list);
	if (!env_variables)
		return ;
	check = ft_check_variables(data, env_variables, 0, 0);
	if (check == 0)
		ft_error_export("");
	ft_free_arr(env_variables);
}
