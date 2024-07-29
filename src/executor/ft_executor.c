/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:00:12 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/29 22:00:07 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_redirections(t_cmd *cmd, int *input_fd, int *output_fd)
{
	if (cmd->input_redir)
	{
		*input_fd = open(cmd->input_file, O_RDONLY);
		if (*input_fd == -1)
			ft_perror("open input file", -1);
	}
	if (cmd->output_redir)
	{
		*output_fd = open(cmd->output_file, cmd->flags, 0644);
		if (*output_fd == -1)
			ft_perror("open output file", -1);
	}
}

int	ft_execute_command(t_data *data, t_cmd *cmd,
	int input_fd, int output_fd)
{
	ft_handle_redirections(cmd, &input_fd, &output_fd);
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			ft_perror("dup2 input", -1);
		close (input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			ft_perror("dup2 output", -1);
		close (output_fd);
	}
	ft_executor(data, cmd);
	return (EXIT_SUCCESS);
}

void	ft_setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		ft_perror("pipe", -1);
}

void	ft_check_input_pipe(t_cmd *current_cmd, int pipefd, int input_fd)
{
	if (current_cmd->next != NULL)
		close (pipefd);
	if (input_fd != STDIN_FILENO)
		close (input_fd);
}

void	ft_exec(t_data *data, int input_fd, int output_fd)
{
	int		pipefd[2];
	pid_t	pid;
	t_cmd	*current_cmd;
	int		status;

	current_cmd = data->cmd_list;
	while (current_cmd != NULL)
	{
		ft_builtins_parent(data, current_cmd);
		if (current_cmd->next != NULL)
			ft_setup_pipe(pipefd);
		pid = fork();
		if (pid == -1)
			ft_perror("fork", -1);
		else if (pid == 0 && current_cmd->next != NULL)
			ft_execute_command(data, current_cmd, input_fd, pipefd[1]);
		else if (pid == 0)
			ft_execute_command(data, current_cmd, input_fd, output_fd);
		else
		{
			ft_check_input_pipe(current_cmd, pipefd[1], input_fd);
			input_fd = pipefd[0];
			current_cmd = current_cmd->next;
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_signal.exit_status = WEXITSTATUS(status);
		}
	}
	if (data->explantion)
	{
		g_signal.exit_status = EXIT_FAILURE;
		data->explantion = 0;
	}
}
