/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:57:32 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 16:30:09 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_redirections(t_cmd *cmd)
{
	int	input_files[10];
	int	output_files[10];

	initialize_file_descriptors(input_files, output_files, 10);
	if (cmd->input_redir && cmd->input_file)
	{
		ft_open_input_files(cmd, input_files);
	}
	if (cmd->output_redir && cmd->output_file)
	{
		ft_open_output_files(cmd, output_files);
	}
}
