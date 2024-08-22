/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_executor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:06:21 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 16:41:11 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cleanup(t_data *data, int *pipefds, pid_t *pid, int cmd_count)
{
	int	i;

	i = -1;
	while (++i < 2 * (cmd_count - 1))
		close(pipefds[i]);
	ft_wait_for_children(data, pid, cmd_count);
	free(pid);
	free(pipefds);
}

t_cmd	*ft_process_command_chain(t_data *data, t_cmd *current_cmd,
		pid_t *pid, int *pipefds)
{
	data->i = 0;
	while (current_cmd != NULL)
	{
		current_cmd = ft_special_cases(data, current_cmd);
		if (current_cmd == NULL
			|| (!ft_strcmp(current_cmd->lexer_list->lexer_comp, "exit")
				&& !current_cmd->next))
			break ;
		ft_process_command(data, current_cmd, pid, pipefds);
		current_cmd = current_cmd->next;
		data->i++;
	}
	return (current_cmd);
}

t_cmd	*ft_exec_command_chain(t_data *data, t_cmd *current_cmd)
{
	t_cmd	*temp_cmd;
	int		cmd_count;
	pid_t	*pid;
	int		*pipefds;

	temp_cmd = current_cmd;
	cmd_count = ft_count_commands(temp_cmd);
	pipefds = ft_initialize_pipefds(cmd_count);
	pid = ft_allocate_pids(cmd_count);
	if (pid == NULL)
	{
		free(pipefds);
		return (NULL);
	}
	data->cmd_count = cmd_count;
	temp_cmd = ft_process_command_chain(data, current_cmd, pid, pipefds);
	ft_cleanup(data, pipefds, pid, cmd_count);
	return (temp_cmd);
}

void	ft_exec(t_data *data, t_cmd *current_cmd)
{
	t_cmd	*current;

	ft_signal_incmd();
	current = ft_exec_command_chain(data, current_cmd);
	if (data->explanation)
	{
		data->exit_status = EXIT_FAILURE;
		data->explanation = 0;
	}
	ft_check_if_heredoc(data);
	if (current && !ft_strcmp(current->commands[0], "exit"))
		ft_mini_exit(data, current);
}

void	ft_prepare_executor(t_data *data)
{
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list;
	while (cmd_list)
	{
		cmd_list->commands = ft_get_commands(cmd_list,
				ft_get_commands_len(cmd_list));
		cmd_list->num_commands = ft_arr_len(cmd_list->commands);
		cmd_list = cmd_list->next;
	}
	ft_exec(data, data->cmd_list);
}
