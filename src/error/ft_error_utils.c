/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:12:10 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/21 17:29:14 by akaterji         ###   ########.fr       */
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
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numberic argument required\n", STDERR_FILENO);
	ft_free_data(data);
	exit (2);
}

void	ft_error_cd(char *str, t_data *data, int flag)
{
	ft_putstr_fd("minishell: cd:", STDERR_FILENO);
	if (flag)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(" :no such file or directory: ", STDERR_FILENO);
	}
	else
		ft_putstr_fd("too many arguments", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = EXIT_FAILURE;
	ft_reset_data(data);
}

void	ft_exit_normal(t_data *data, t_lexer *lexer_list)
{
	int		exit_code;
	char	*str;

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
	str = ft_itoa(exit_code);
	ft_putstr_fd("minishell: exit ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(str);
	exit (exit_code);
}

void	ft_check_export(t_data *data)
{
	if (data->cmd_count == 1)
		ft_reset_data(data);
}
