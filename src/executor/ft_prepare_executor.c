/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_executor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:06:21 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/27 11:35:25 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_prepare_executor(t_data *data)
{
	int		input_fd;
	int		output_fd;

	signal(SIGQUIT, ft_sigquit_handler);
	input_fd = STDIN_FILENO;
	output_fd = STDOUT_FILENO;
	ft_mini_exit(data);
	ft_exec(data, input_fd, output_fd);
}

int	ft_executor(t_data *data, t_cmd *cmd_list)
{
	char	**cmd;

	cmd = cmd_list->commands;
	if (cmd && cmd_list->lexer_list->token == MINICMD)
		ft_builtins_child(data, cmd_list);
	else if (cmd)
	{
		execvp(cmd[0], cmd);
		ft_perror("execvp command", -1);
	}
	return (EXIT_FAILURE);
}
