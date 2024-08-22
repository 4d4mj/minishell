/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_cd_utils_three.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:51:31 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/11 12:32:28 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_env(t_data *data, char *key, char *value)
{
	int		i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], key, ft_strlen(key)))
		{
			free(data->envp[i]);
			data->envp[i] = ft_strjoin(key, value);
			return ;
		}
		i++;
	}
}

void	ft_addenv(t_data *data, char *key, char *value)
{
	char	*new_var;
	char	**new_arr;
	size_t	i;
	size_t	len;

	len = ft_arr_len(data->envp);
	new_var = ft_strjoin(key, value);
	new_arr = ft_calloc(sizeof(char *), len + 2);
	if (!new_arr)
		return ;
	i = -1;
	while (++i < len)
		new_arr[i] = ft_strdup(data->envp[i]);
	new_arr[len] = ft_strdup(new_var);
	new_arr[len + 1] = NULL;
	ft_free_arr(data->envp);
	data->envp = new_arr;
	free(new_var);
}

void	ft_set_paths(t_data *data, char *new_path)
{
	char	*old_path;

	if (data->pwd)
		old_path = ft_strdup(data->pwd);
	else
		old_path = ft_strdup(new_path);
	free(data->old_pwd);
	data->old_pwd = old_path;
	free(data->pwd);
	data->pwd = ft_strdup(new_path);
}

int	ft_getenv(t_data *data, char *key)
{
	int		i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], key, ft_strlen(key)))
			return (1);
		i++;
	}
	return (0);
}
