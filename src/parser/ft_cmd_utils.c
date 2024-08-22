/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:01:18 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 00:27:05 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*ft_fill_cmd(t_data *data, t_lexer *lexer_list, t_cmd *cmd_list, int i)
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
	ft_parse_cmd(data, cmd_list);
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
	cmd_new->heredoc_num = 0;
	cmd_new->heredoc_index = 0;
	return (cmd_new);
}
