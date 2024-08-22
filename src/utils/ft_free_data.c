/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:50:25 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 04:18:37 by ajabado          ###   ########.fr       */
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

void	ft_clean_heredoc(t_cmd *cmd_list)
{
	int	i;

	i = -1;
	while (++i < cmd_list->heredoc_num)
		unlink(cmd_list->heredoc[i]);
}

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->cmd_list && data->cmd_list->heredoc)
		ft_clean_heredoc(data->cmd_list);
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
	data->home = NULL;
	if (data->pwd != NULL)
		free(data->pwd);
	data->pwd = NULL;
	if (data->old_pwd != NULL)
		free(data->old_pwd);
	data->old_pwd = NULL;
	if (data->readline)
		free(data->readline);
	data->readline = NULL;
}
