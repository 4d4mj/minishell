/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:36:39 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/27 14:27:21 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

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
	g_signal.exit_status = 2;
	ft_reset_data(data);
	return (EXIT_FAILURE);
}

void	ft_error(char *str, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	g_signal.exit_status = EXIT_FAILURE;
	ft_reset_data(data);
}

void	ft_error_exit(char *str, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_free_data(data);
	exit (EXIT_FAILURE);
}

void	ft_error_cmd(char *str, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_signal.exit_status = 127;
	ft_reset_data(data);
}

void	ft_error_export(char *str)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (str)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\': is ", STDERR_FILENO);
	}
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	g_signal.exit_status = EXIT_FAILURE;
}
