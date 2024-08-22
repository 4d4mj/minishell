/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:59:22 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 17:39:24 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_arr_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_arrdup_modified(t_data *data, char **arr, char *str)
{
	char	**ret_arr;
	size_t	i;
	size_t	len;

	len = ft_arr_len(arr);
	ret_arr = ft_calloc(sizeof(char *), len + 2);
	if (!ret_arr)
		return ;
	i = -1;
	while (++i < len)
	{
		ret_arr[i] = ft_strdup(arr[i]);
		if (ret_arr[i] == NULL)
		{
			ft_free_arr(ret_arr);
			return ;
		}
	}
	ret_arr[len] = ft_strdup(str);
	ret_arr[len + 1] = NULL;
	data->envp = ret_arr;
}

char	**ft_arrdup(char **arr)
{
	char	**ret_arr;
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	ret_arr = ft_calloc(sizeof(char *), i + 1);
	if (!ret_arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		ret_arr[i] = ft_strdup(arr[i]);
		if (ret_arr[i] == NULL)
		{
			ft_free_arr(ret_arr);
			return (ret_arr);
		}
		i++;
	}
	return (ret_arr);
}

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
	env_variables[len] = NULL;
	return (env_variables);
}
