/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:09:57 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/11 15:32:32 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_count_pipes(t_data *data)
{
	t_lexer	*current_lexer;

	current_lexer = data->lexer_list;
	data->pipes = 0;
	while (current_lexer)
	{
		if (current_lexer->token == PIPE)
			data->pipes++;
		current_lexer = current_lexer->next;
	}
}

int	ft_count_args(t_lexer *lexer_list)
{
	t_lexer	*current_lexer;
	int		i;

	i = 0;
	current_lexer = lexer_list;
	while (current_lexer != NULL && current_lexer->token != PIPE)
	{
		i++;
		current_lexer = current_lexer->next;
	}
	return (i);
}

void	ft_cmd_add_back(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*current_cmd;

	current_cmd = *cmd_list;
	if (*cmd_list == NULL)
	{
		*cmd_list = new_cmd;
		return ;
	}
	while (current_cmd->next != NULL)
		current_cmd = current_cmd->next;
	current_cmd->next = new_cmd;
	new_cmd->prev = current_cmd;
}

int	ft_handle_pipe_error(t_data *data, t_lexer *lexer_list)
{
	if (lexer_list && (lexer_list->token == PIPE
			|| lexer_list->token == AND || lexer_list->token == SEMI))
		return (ft_error_double_token(data, lexer_list->token));
	if (!lexer_list)
	{
		ft_error("unable to assign memory\n", data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*find_command_in_paths(t_data *data, char *str)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (data->paths[i])
	{
		path = ft_strjoin(data->paths[i], str);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
