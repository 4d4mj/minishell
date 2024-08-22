/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:04:28 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 04:52:37 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_shlvl(t_data *data)
{
	int		i;
	char	*tmp;
	int		flag;

	i = -1;
	flag = 0;
	while (data->old_envp[++i])
	{
		if (!ft_strncmp(data->old_envp[i], "SHLVL", ft_strlen("SHLVL")))
		{
			tmp = ft_strdup(data->old_envp[i]);
			free(data->old_envp[i]);
			data->old_envp[i] = ft_get_shlvl(tmp);
			free(tmp);
			flag = 1;
		}
	}
	if (!flag)
	{
		ft_arrdup_modified(data, data->old_envp, "SHLVL=1");
		ft_free_arr(data->old_envp);
		data->old_envp = ft_arrdup(data->envp);
	}
}

void	ft_init(t_data *data, char **envp)
{
	data->readline = NULL;
	data->lexer_list = NULL;
	data->cmd_list = NULL;
	data->env_list = NULL;
	data->envp = NULL;
	data->old_envp = NULL;
	data->home = NULL;
	data->pwd = getcwd(NULL, 0);
	data->old_pwd = NULL;
	data->explanation = 0;
	data->quote_heredoc = 0;
	data->cmd_count = 0;
	data->i = 0;
	data->old_envp = ft_arrdup(envp);
	data->stop_heredoc = 0;
	ft_update_shlvl(data);
	ft_arrdup_modified(data, data->old_envp, "?=0");
	ft_free_arr(envp);
	envp = data->envp;
	ft_arrdup_modified(data, envp, "$=0");
	ft_free_arr(envp);
	ft_initialize_data(data);
	ft_minishell_loop(data);
}

void	ft_implement_data(t_data *data)
{
	data->cmd_list = NULL;
	data->lexer_list = NULL;
	data->readline = NULL;
	data->explanation = 0;
}

void	ft_initialize_data(t_data *data)
{
	ft_find_pwd(data);
	ft_find_path(data);
	ft_implement_data(data);
	ft_init_signal();
}
