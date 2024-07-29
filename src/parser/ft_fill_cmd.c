/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:04:40 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/26 10:07:26 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parse_cmd(t_cmd *cmd_list)
{
	t_lexer	*lexer_list;

	lexer_list = cmd_list->lexer_list;
	while (lexer_list != NULL)
	{
		if (lexer_list->token == INPUT
			|| lexer_list->token == HEREDOC)
		{
			cmd_list->input_file = ft_strdup(lexer_list->next->lexer_comp);
			if (lexer_list->token == INPUT)
				cmd_list->input_redir = 1;
			lexer_list = lexer_list->next;
		}
		else if (lexer_list->token == APPEND
			|| lexer_list->token == TRUNC)
		{
			cmd_list->output_file = ft_strdup(lexer_list->next->lexer_comp);
			cmd_list->output_redir = 1;
			cmd_list->flags = O_WRONLY | O_CREAT | O_TRUNC;
			if (lexer_list->token == APPEND)
				cmd_list->flags = O_WRONLY | O_CREAT | O_APPEND;
			lexer_list = lexer_list->next;
		}
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
			&& lexer_list->token <= HEREDOC)
			lexer_list = lexer_list->next;
		else
			i++;
		lexer_list = lexer_list->next;
	}
	return (i);
}

char	**ft_get_commands(t_cmd *cmd_list)
{
	char	**commands;
	t_lexer	*lexer_list;
	int		i;

	i = ft_get_commands_len(cmd_list);
	commands = ft_calloc(sizeof(char *), i + 1);
	if (!commands)
		return (NULL);
	lexer_list = cmd_list->lexer_list;
	i = 0;
	while (lexer_list)
	{
		if (lexer_list->next && lexer_list->token >= TRUNC
			&& lexer_list->token <= HEREDOC)
			lexer_list = lexer_list->next;
		else
			commands[i++] = ft_strdup(lexer_list->lexer_comp);
		lexer_list = lexer_list->next;
	}
	commands[i] = NULL;
	return (commands);
}

t_lexer	*ft_fill_cmd(t_lexer *lexer_list, t_cmd *cmd_list, int i)
{
	int		arg_size;
	t_lexer	*current_lexer;
	char	*dup_lexer;

	arg_size = ft_count_args(lexer_list);
	current_lexer = lexer_list;
	while (current_lexer != NULL && ++i < arg_size)
	{
		dup_lexer = ft_strdup(current_lexer->lexer_comp);
		ft_lexer_add(dup_lexer, current_lexer->token,
			&cmd_list->lexer_list);
		current_lexer = current_lexer->next;
	}
	ft_parse_cmd(cmd_list);
	cmd_list->commands = ft_get_commands(cmd_list);
	cmd_list->num_commands = ft_arr_len(cmd_list->commands);
	return (current_lexer);
}

t_cmd	*ft_cmd_new(void)
{
	t_cmd	*cmd_new;

	cmd_new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd_new)
		return (NULL);
	cmd_new->lexer_list = NULL;
	cmd_new->next = NULL;
	cmd_new->prev = NULL;
	cmd_new->commands = NULL;
	cmd_new->heredoc = NULL;
	cmd_new->input_file = NULL;
	cmd_new->output_file = NULL;
	cmd_new->flags = 0;
	cmd_new->input_redir = 0;
	cmd_new->output_redir = 0;
	cmd_new->num_commands = 0;
	return (cmd_new);
}
