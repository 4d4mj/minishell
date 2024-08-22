/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:36:39 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 03:45:29 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error_double_token(t_data *data, int token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else if (token == HEREDOC)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == INPUT)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == APPEND)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == TRUNC)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == AND)
		ft_putstr_fd("'&&'\n", STDERR_FILENO);
	else if (token == SEMI)
		ft_putstr_fd("';;'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = 2;
	ft_reset_data(data);
	return (EXIT_FAILURE);
}

void	ft_error(char *str, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (!data)
		exit(1);
	data->exit_status = EXIT_FAILURE;
	ft_reset_data(data);
}

void	ft_error_exit(char *str, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_free_data(data);
	exit (EXIT_FAILURE);
}

void	ft_error_export_invalid_option(t_data *data, char *str)
{
	if (str && str[0] == '-')
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putchar_fd(str[0], STDERR_FILENO);
		if (str[1])
			ft_putchar_fd(str[1], STDERR_FILENO);
		ft_putstr_fd("\': ", STDERR_FILENO);
		ft_putendl_fd("is invalid option", STDERR_FILENO);
		data->exit_status = 2;
	}
}

void	ft_error_export(t_data *data, char *str, int flag)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (str && str[0] != '-')
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\': ", STDERR_FILENO);
		if (flag == 0)
		{
			data->exit_status = 1;
			ft_putendl_fd("is not a valid identifier", STDERR_FILENO);
		}
		else if (flag == 1)
		{
			data->exit_status = 127;
			ft_putendl_fd("command not found", STDERR_FILENO);
		}
		else if (flag == 2)
		{
			data->exit_status = 0;
			ft_putendl_fd("event not found ", STDERR_FILENO);
		}
	}
	else
		ft_error_export_invalid_option(data, str);
}
