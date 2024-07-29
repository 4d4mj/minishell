/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:12:10 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/29 22:40:09 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_perror(char *str, int fd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	if (fd)
		close (fd);
	exit(EXIT_FAILURE);
}

void	ft_error_exit_numeric(char *str, t_data *data)
{
	ft_putstr_fd("minishell: exit: 127", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numberic argument required\n", STDERR_FILENO);
	ft_free_data(data);
	exit (127);
}

void	ft_error_cd(char *str, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("cd :no such file or directory: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_signal.exit_status = EXIT_FAILURE;
	ft_reset_data(data);
}

void	ft_exit_normal(t_data *data, t_lexer *lexer_list)
{
	int	exit_code;

	exit_code = 0;
	if (lexer_list->next)
	{
		exit_code = ft_atoi(lexer_list->next->lexer_comp);
		if (exit_code > 255)
		{
			while (exit_code > 255)
				exit_code -= 256;
		}
		else if (exit_code < 0)
		{
			while (exit_code < 0)
				exit_code += 256;
		}
	}
	ft_free_data(data);
	exit(exit_code);
}
