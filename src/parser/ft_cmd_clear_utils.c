/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_clear_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:04:08 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/23 12:56:10 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cmd_clear_list(t_cmd **cmd_list)
{
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;

	if (!cmd_list || !*cmd_list)
		return ;
	current_cmd = *cmd_list;
	while (current_cmd != NULL)
	{
		next_cmd = current_cmd->next;
		if (current_cmd->lexer_list != NULL)
			ft_lexer_clear_list(&current_cmd->lexer_list);
		if (current_cmd->commands)
			ft_free_arr(current_cmd->commands);
		if (current_cmd->input_file)
			free (current_cmd->input_file);
		if (current_cmd->output_file)
			free (current_cmd->output_file);
		if (current_cmd->heredoc)
			free (current_cmd->heredoc);
		free(current_cmd);
		current_cmd = next_cmd;
	}
	*cmd_list = NULL;
}
