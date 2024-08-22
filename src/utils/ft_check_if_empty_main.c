/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_if_empty_main.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:37:32 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 12:09:42 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_if_empty(t_data *data)
{
	if ((data->readline[0] == ':') && (data->readline[1] == '\0'
			|| is_whitespace(data->readline[1])))
		return (ft_reset_data(data));
	if (data->readline[0] == '.')
	{
		if (data->readline[1] == '\0')
		{
			ft_putstr_fd("minishell: .: filename argument required\n",
				STDERR_FILENO);
			data->exit_status = 2;
			ft_reset_data(data);
		}
		else if (data->readline[1] == '.' && data->readline[2] == '\0')
			ft_error_cmd("..", data);
	}
}
