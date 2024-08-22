/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:37:02 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 00:14:56 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmd_delete_prev(t_cmd **cmd_list, t_cmd *next_cmd)
{
	t_cmd	*current_cmd;

	current_cmd = NULL;
	next_cmd = next_cmd->next;
	while (*cmd_list != next_cmd)
	{
		current_cmd = (*cmd_list)->next;
		if ((*cmd_list)->lexer_list != NULL)
			ft_lexer_clear_list(&(*cmd_list)->lexer_list);
		if ((*cmd_list)->commands)
			ft_free_arr((*cmd_list)->commands);
		if ((*cmd_list)->input_file)
			free((*cmd_list)->input_file);
		if ((*cmd_list)->output_file)
			free((*cmd_list)->output_file);
		if ((*cmd_list)->heredoc)
			ft_free_arr((*cmd_list)->heredoc);
		(*cmd_list)->heredoc = NULL;
		if ((*cmd_list))
			free(*cmd_list);
		*cmd_list = NULL;
		*cmd_list = current_cmd;
	}
	return (0);
}

void	ft_clean_executed_command(t_data *data, t_cmd *cmd_list)
{
	int		i;
	char	**commands;

	(void) data;
	ft_lexer_del_first(&cmd_list->lexer_list);
	i = ft_arr_len(cmd_list->commands);
	commands = ft_calloc(sizeof(char *), i);
	if (!commands)
		return ;
	i = 0;
	while (cmd_list->commands && cmd_list->commands[++i])
		commands[i - 1] = ft_strdup(cmd_list->commands[i]);
	commands[i - 1] = NULL;
	ft_free_arr(cmd_list->commands);
	cmd_list->commands = commands;
}

void	ft_clean_executed_commands(t_data *data, t_cmd *cmd_list)
{
	int		i;
	t_lexer	*lexer_list;

	i = 0;
	lexer_list = cmd_list->lexer_list;
	while (lexer_list && lexer_list->token == ARG)
	{
		i++;
		lexer_list = lexer_list->next;
	}
	while (i--)
		ft_clean_executed_command(data, cmd_list);
}
