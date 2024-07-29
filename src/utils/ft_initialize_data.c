/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:04:28 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/27 13:08:28 by akaterji         ###   ########.fr       */
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

void	ft_implement_data(t_data *data)
{
	data->cmd_list = NULL;
	data->lexer_list = NULL;
	data->readline = NULL;
	data->pipes = 0;
	data->explantion = 0;
	g_signal.in_cmd = 0;
	g_signal.in_heredoc = 0;
	g_signal.stop_heredoc = 0;
}

void	ft_initialize_data(t_data *data)
{
	ft_find_pwd(data);
	ft_find_path(data);
	ft_implement_data(data);
	ft_init_signal();
}
