/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:40:35 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/29 14:00:14 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_env_new(char *str)
{
	t_env	*new_env;
	int		i;
	char	*var;
	char	*comp;

	i = 0;
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->next = NULL;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	var = ft_substr(str, 0, i);
	comp = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	new_env->env_var = ft_strjoin("$", var);
	if (comp == NULL)
		comp = ft_strdup("' '");
	new_env->env_comp = ft_strdup(comp);
	free(var);
	free(comp);
	return (new_env);
}

void	ft_env_add_back(t_env **env_list, t_env *new_env)
{
	t_env	*current_env;

	current_env = *env_list;
	if (*env_list == NULL)
	{
		*env_list = new_env;
		return ;
	}
	while (current_env->next != NULL)
		current_env = current_env->next;
	current_env->next = new_env;
}

void	ft_add_env_list(char *str, t_env **env_list)
{
	t_env	*new_env;

	new_env = ft_env_new(str);
	if (!new_env)
		return ;
	ft_env_add_back(env_list, new_env);
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
