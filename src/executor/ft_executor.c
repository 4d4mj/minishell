/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:44:42 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 03:44:57 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_pid(pid_t *pid, int i)
{
	if (pid[i] == -1)
	{
		ft_perror("fork", -1);
		exit(EXIT_FAILURE);
	}
}

void	ft_pipefds(t_cmd *current, int *pipefds, int i)
{
	if (i > 0)
	{
		if (dup2(pipefds[(i - 1) * 2], STDIN_FILENO) == -1)
		{
			ft_perror("dup2 input", -1);
			exit(EXIT_FAILURE);
		}
	}
	if (current->next != NULL)
	{
		if (dup2(pipefds[i * 2 + 1], STDOUT_FILENO) == -1)
		{
			ft_perror("dup2 output", -1);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_executor(t_data *data, t_cmd *cmd_list)
{
	char	**cmd;

	if (cmd_list && (cmd_list->lexer_list->token == MINICMD
			|| cmd_list->lexer_list->token == HEREDOC))
		ft_builtins_parent(data, cmd_list);
	cmd = cmd_list->commands;
	if (cmd && cmd[0])
	{
		if (cmd_list->lexer_list->next
			&& cmd_list->lexer_list->next->token == REDIRECTION)
			;
		else
		{
			execve(cmd[0], cmd, data->old_envp);
			ft_perror("execve command", -1);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_process_command(t_data *data, t_cmd *current_cmd,
			pid_t *pid, int *pipefds)
{
	int	cmd_count;
	int	i;
	int	j;

	j = -1;
	i = data->i;
	cmd_count = data->cmd_count;
	pid[i] = fork();
	ft_check_pid(pid, i);
	if (pid[i] == 0)
	{
		ft_reset_signal();
		ft_pipefds(current_cmd, pipefds, i);
		while (++j < 2 * (cmd_count - 1))
			close(pipefds[j]);
		ft_handle_redirections(current_cmd);
		ft_executor(data, current_cmd);
	}
}
