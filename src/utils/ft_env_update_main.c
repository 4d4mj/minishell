/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_update_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:35:42 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 12:33:06 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_envp(t_data *data)
{
	char	*tmp;
	char	*value;
	int		i;

	i = -1;
	while (data->envp[++i])
	{
		if (!ft_strncmp(data->envp[i], "?=", 2))
		{
			value = ft_itoa(data->exit_status);
			tmp = ft_strjoin("?=", value);
			free(data->envp[i]);
			data->envp[i] = ft_strdup(tmp);
			ft_free_four(tmp, value, NULL, NULL);
		}
		else if (!ft_strncmp(data->envp[i], "$=", 2))
		{
			value = ft_itoa(getpid());
			tmp = ft_strjoin("$=", value);
			free(data->envp[i]);
			data->envp[i] = ft_strdup(tmp);
			ft_free_four(tmp, value, NULL, NULL);
		}
	}
}

void	ft_update_env_list(t_data *data)
{
	t_env	*env_list;
	int		i;

	i = -1;
	env_list = NULL;
	while (data->envp[++i])
		ft_add_env_list(data->envp[i], &env_list);
	if (data->env_list)
		ft_env_clear_list(&data->env_list);
	data->env_list = env_list;
}

void	ft_env_update(t_data *data)
{
	ft_envp(data);
	ft_update_env_list(data);
}
