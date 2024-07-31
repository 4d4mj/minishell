/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:03:48 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/30 17:56:51 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_minicmd(char *str)
{
	if (!ft_strcmp(str, "exit")
		|| !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "echo"))
		return (1);
	return (0);
}

void	ft_find_command_path(t_data *data, t_lexer *lexer_list,
	int i, char *str)
{
	char	*path;

	if (ft_check_minicmd(str))
	{
		lexer_list->token = MINICMD;
		return ;
	}
	if (str)
	{
		while (data->paths[++i])
		{
			path = ft_strjoin(data->paths[i], str);
			if (access(path, F_OK) == 0)
			{
				lexer_list->token = CMD;
				lexer_list->path = ft_strdup(path);
				free(path);
				return ;
			}
			free(path);
		}
		lexer_list->token = ARG;
	}
}

void	ft_check_start_io_cmd(t_cmd *current_cmd, t_data *data)
{
	if (!(current_cmd->lexer_list->token >= CMD
			&& current_cmd->lexer_list->token <= MINICMD))
		ft_error_cmd (current_cmd->lexer_list->lexer_comp, data);
}

void	ft_check_cmd(t_data *data)
{
	t_cmd	*current_cmd;
	t_lexer	*lexer_list;
	char	*str;

	current_cmd = data->cmd_list;
	while (current_cmd != NULL)
	{
		lexer_list = current_cmd->lexer_list;
		while (lexer_list != NULL)
		{
			if (lexer_list->token == EMPTY)
			{
				str = lexer_list->lexer_comp;
				ft_find_command_path(data, lexer_list, -1, str);
			}
			lexer_list = lexer_list->next;
		}
		ft_check_start_io_cmd(current_cmd, data);
		current_cmd = current_cmd->next;
	}
}

int	ft_parser(t_data *data)
{
	t_cmd	*cmd_node;
	t_lexer	*tmp_lexer;

	ft_count_pipes(data);
	tmp_lexer = data->lexer_list;
	if (ft_handle_pipe_error(data, tmp_lexer))
		return (EXIT_FAILURE);
	while (tmp_lexer != NULL)
	{
		if (tmp_lexer && tmp_lexer->token == PIPE)
			tmp_lexer = tmp_lexer->next;
		if (ft_handle_pipe_error(data, tmp_lexer))
			return (EXIT_FAILURE);
		cmd_node = ft_cmd_new();
		if (!cmd_node)
			ft_error ("memory error: unable to assign memory\n", data);
		tmp_lexer = ft_fill_cmd(tmp_lexer, cmd_node, -1);
		ft_cmd_add_back(&data->cmd_list, cmd_node);
	}
	ft_check_cmd(data);
	return (EXIT_SUCCESS);
}
