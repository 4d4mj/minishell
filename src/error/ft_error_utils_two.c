/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:33:19 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 12:09:02 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_env(t_data *data, char *str)
{
	ft_putstr_fd("minishell: env: ", STDERR_FILENO);
	if (str)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\': is ", STDERR_FILENO);
	}
	ft_putendl_fd("no such file or directory", STDERR_FILENO);
	data->exit_status = 127;
}

void	ft_error_unset(t_data *data, char *str, int flag)
{
	if (flag != 4)
		ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
	if (str && flag != 4)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\': is ", STDERR_FILENO);
	}
	if (flag == 1 || flag == 3)
	{
		ft_putendl_fd("not a valid identifier", STDERR_FILENO);
		data->exit_status = EXIT_FAILURE;
	}
	else if (flag == 2)
	{
		ft_putendl_fd("invalid option", STDERR_FILENO);
		data->exit_status = 2;
	}
	else if (flag == 5)
	{
		ft_putendl_fd("command not found", STDERR_FILENO);
		data->exit_status = 127;
	}
	else
		data->exit_status = 0;
}

void	ft_error_pwd(t_data *data, char *str)
{
	char	*new_str;

	ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
	if (str)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		if (ft_strlen(str) > 2)
		{
			new_str = ft_substr(str, 0, 2);
			ft_putstr_fd(new_str, STDERR_FILENO);
			free(new_str);
		}
		else
			ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\': ", STDERR_FILENO);
	}
	ft_putendl_fd("invalid option", STDERR_FILENO);
	data->exit_status = 2;
}

void	ft_error_cmd(char *str, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	data->exit_status = 127;
	ft_reset_data(data);
}
