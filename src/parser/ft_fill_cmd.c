/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:04:40 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 00:44:34 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input_redirection(t_data *data, t_cmd *cmd_list,
	t_lexer *lexer_list)
{
	if (lexer_list->token == HEREDOC)
	{
		cmd_list->heredoc_num += 1;
		ft_add_arr(cmd_list, cmd_list->heredoc,
			lexer_list->next->lexer_comp, 2);
		if (!cmd_list->heredoc)
			ft_error_double_token(data, HEREDOC);
		lexer_list->next->token = REDIRECTION;
	}
	else
	{
		ft_add_arr(cmd_list, cmd_list->input_file,
			lexer_list->next->lexer_comp, 1);
		if (!lexer_list->next->lexer_comp)
			ft_error_double_token(data, INPUT);
		if (lexer_list->token == INPUT)
			cmd_list->input_redir++;
		lexer_list->next->token = REDIRECTION;
	}
	lexer_list = lexer_list->next;
}

void	handle_output_redirection(t_data *data, t_cmd *cmd_list,
	t_lexer *lexer_list)
{
	ft_add_arr(cmd_list, cmd_list->output_file,
		lexer_list->next->lexer_comp, 0);
	if (!lexer_list->next->lexer_comp)
		ft_error_double_token(data, TRUNC);
	cmd_list->output_redir++;
	cmd_list->flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (lexer_list->token == APPEND)
		cmd_list->flags = O_WRONLY | O_CREAT | O_APPEND;
	lexer_list->next->token = REDIRECTION;
	lexer_list = lexer_list->next;
}

void	ft_parse_cmd(t_data *data, t_cmd *cmd_list)
{
	t_lexer	*lexer_list;

	lexer_list = cmd_list->lexer_list;
	while (lexer_list != NULL)
	{
		if (lexer_list->token == INPUT || lexer_list->token == HEREDOC)
			handle_input_redirection(data, cmd_list, lexer_list);
		else if (lexer_list->token == APPEND || lexer_list->token == TRUNC)
			handle_output_redirection(data, cmd_list, lexer_list);
		lexer_list = lexer_list->next;
	}
}

int	ft_get_commands_len(t_cmd *cmd_list)
{
	int		i;
	t_lexer	*lexer_list;

	i = 0;
	lexer_list = cmd_list->lexer_list;
	while (lexer_list)
	{
		if (lexer_list->next && lexer_list->token >= TRUNC
			&& lexer_list->token <= APPEND)
			lexer_list = lexer_list->next;
		else
			i++;
		lexer_list = lexer_list->next;
	}
	return (i);
}

char	**ft_get_commands(t_cmd *cmd_list, int i)
{
	char	**commands;
	t_lexer	*lexer_list;

	commands = ft_calloc(sizeof(char *), i + 1);
	if (!commands)
		return (NULL);
	lexer_list = cmd_list->lexer_list;
	i = 0;
	while (lexer_list)
	{
		if (lexer_list->next && lexer_list->token >= INPUT
			&& lexer_list->token <= HEREDOC)
			;
		else if (lexer_list->next && lexer_list->token >= TRUNC
			&& lexer_list->token <= APPEND)
			lexer_list = lexer_list->next;
		else if (lexer_list && lexer_list->lexer_comp != NULL)
		{
			commands[i] = ft_strdup(lexer_list->lexer_comp);
			i++;
		}
		lexer_list = lexer_list->next;
	}
	commands[i] = NULL;
	return (commands);
}
