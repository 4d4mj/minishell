/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:50:25 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/30 09:01:30 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env_clear_list(t_env **env_list)
{
	t_env	*current_env;

	if (!env_list || !*env_list)
		return ;
	while (*env_list)
	{
		current_env = (*env_list)->next;
		if ((*env_list)->env_comp)
			free((*env_list)->env_comp);
		if ((*env_list)->env_var)
			free((*env_list)->env_var);
		free((*env_list));
		*env_list = current_env;
	}
	*env_list = NULL;
}

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->cmd_list)
		ft_cmd_clear_list(&data->cmd_list);
	if (data->lexer_list)
		ft_lexer_clear_list(&data->lexer_list);
	if (data->env_list)
		ft_env_clear_list(&data->env_list);
	if (data->paths)
		ft_free_arr(data->paths);
	if (data->home)
		free(data->home);
	if (data->pwd)
		free(data->pwd);
	if (data->old_pwd)
		free(data->old_pwd);
	if (data->readline)
		free(data->readline);
}
