/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils_four.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:22:42 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 16:25:45 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialize_file_descriptors(int *input_fds, int *output_fds,
	int max_files)
{
	int	i;

	i = -1;
	while (++i < max_files)
	{
		input_fds[i] = -1;
		output_fds[i] = -1;
	}
}

void	ft_open_input_files(t_cmd *cmd, int *input_files)
{
	int	i;

	i = -1;
	while (++i < cmd->input_redir)
	{
		input_files[i] = open(cmd->input_file[i], O_RDONLY);
		if (input_files[i] == -1)
		{
			perror("open input file");
			fprintf(stderr, "Failed to open file: %s\n", cmd->input_file[i]);
			exit(EXIT_FAILURE);
		}
		if (dup2(input_files[i], STDIN_FILENO) == -1)
			ft_perror("dup2 input", -1);
		close (input_files[i]);
	}
}

void	ft_open_output_files(t_cmd *cmd, int *output_files)
{
	int	i;

	i = -1;
	while (++i < cmd->output_redir)
	{
		output_files[i] = open(cmd->output_file[i], cmd->flags, 0644);
		if (output_files[i] == -1)
		{
			perror("open output file");
			fprintf(stderr, "Failed to open file: %s\n", cmd->output_file[i]);
			exit(EXIT_FAILURE);
		}
		if (dup2(output_files[i], STDOUT_FILENO) == -1)
			ft_perror("dup2 output", -1);
		close (output_files[i]);
	}
}
