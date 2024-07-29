/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:26:43 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/28 18:27:30 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_expander(t_data *data)
{
	char	*tmp;
	char	*exit_status;
	int		i;
	t_env	*env_list;

	env_list = NULL;
	i = -1;
	while (data->envp[++i])
	{
		if (!ft_strncmp(data->envp[i], "?=", 2))
		{
			exit_status = ft_itoa(g_signal.exit_status);
			tmp = ft_strjoin("?=", exit_status);
			free(exit_status);
			free(data->envp[i]);
			data->envp[i] = ft_strdup(tmp);
			free(tmp);
		}
		ft_add_env_list(data->envp[i], &env_list);
	}
	if (data->env_list)
		ft_env_clear_list(&data->env_list);
	data->env_list = env_list;
}
