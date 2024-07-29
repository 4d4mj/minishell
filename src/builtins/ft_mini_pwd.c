/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:44:52 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/25 15:39:48 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_mini_pwd(t_data *data, t_cmd *cmd_list)
{
	(void) cmd_list;
	ft_putendl_fd(data->pwd, STDOUT_FILENO);
}
