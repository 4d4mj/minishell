/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:44:26 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/26 14:28:45 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_mini_env(t_data *data, t_cmd *cmd_list)
{
	int	i;

	i = 0;
	(void) cmd_list;
	while (data->envp[i])
	{
		ft_putendl_fd(data->envp[i], STDOUT_FILENO);
		i++;
	}
	exit (EXIT_SUCCESS);
}
