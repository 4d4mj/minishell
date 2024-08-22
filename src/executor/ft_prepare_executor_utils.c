/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_executor_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:20:04 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 03:46:15 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_if_heredoc(t_data *data)
{
	t_cmd	*current;

	current = data->cmd_list;
	while (current)
		current = current->next;
}

int	ft_count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd != NULL)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	*ft_initialize_pipefds(int cmd_count)
{
	int	*pipefds;
	int	num_pipes;
	int	i;

	i = -1;
	num_pipes = cmd_count - 1;
	if (num_pipes <= 0)
		return (NULL);
	pipefds = malloc(2 * num_pipes * sizeof(int));
	if (pipefds == NULL)
	{
		ft_perror("malloc", -1);
		return (NULL);
	}
	while (++i < num_pipes)
	{
		if (pipe(pipefds + i * 2) == -1)
		{
			ft_perror("pipe", -1);
			free(pipefds);
			return (NULL);
		}
	}
	return (pipefds);
}

pid_t	*ft_allocate_pids(int cmd_count)
{
	pid_t	*pid;
	int		i;

	i = -1;
	pid = malloc(cmd_count * sizeof(pid_t));
	if (pid == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	while (++i < cmd_count)
		pid[i] = -1;
	return (pid);
}

void	ft_wait_for_children(t_data *data, pid_t *pid, int cmd_count)
{
	int	status;
	int	i;

	i = -1;
	status = 0;
	while (++i < cmd_count)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
}
