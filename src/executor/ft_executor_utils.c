/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:16:08 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 05:37:02 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*handle_export(t_data *data, t_cmd *cmd_list, int *flag)
{
	t_lexer	*lexer_list;

	lexer_list = cmd_list->lexer_list;
	if (!ft_strcmp(lexer_list->lexer_comp, "export"))
	{
		*flag = 1;
		if (lexer_list->next && !cmd_list->next && !cmd_list->output_file)
		{
			ft_mini_export(data, cmd_list, 0);
			return (cmd_list->next);
		}
		else if (lexer_list->next && cmd_list->next)
			return (cmd_list->next);
	}
	return (cmd_list);
}

t_cmd	*handle_cd(t_data *data, t_cmd *cmd_list, int *flag)
{
	if (!ft_strcmp(cmd_list->lexer_list->lexer_comp, "cd"))
	{
		*flag = 1;
		if (!cmd_list->next)
		{
			ft_mini_cd(data, cmd_list);
			return (cmd_list->next);
		}
		else
			return (cmd_list->next);
	}
	return (cmd_list);
}

t_cmd	*handle_unset(t_data *data, t_cmd *cmd_list, int *flag)
{
	if (!ft_strcmp(cmd_list->lexer_list->lexer_comp, "unset"))
	{
		*flag = 1;
		if (!cmd_list->next)
		{
			ft_mini_unset(data, cmd_list, 0);
			return (cmd_list->next);
		}
		else
			return (cmd_list->next);
	}
	return (cmd_list);
}

t_cmd	*handle_heredoc(t_data *data, t_cmd *cmd_list)
{
	while (cmd_list->heredoc_index < cmd_list->heredoc_num
		&& cmd_list->heredoc[cmd_list->heredoc_index])
	{
		data->stop_heredoc = 0;
		ft_here_doc(data, cmd_list->heredoc[cmd_list->heredoc_index]);
		cmd_list->heredoc_index++;
	}
	if (cmd_list->heredoc_num
		&& cmd_list->heredoc_index == cmd_list->heredoc_num)
	{
		if (cmd_list->lexer_list->token == HEREDOC
			&& !cmd_list->lexer_list->next->next)
			return (cmd_list->next);
	}
	return (cmd_list);
}

t_cmd	*ft_special_cases(t_data *data, t_cmd *cmd_list)
{
	int	flag;

	flag = 0;
	cmd_list = handle_export(data, cmd_list, &flag);
	if (flag)
		return (cmd_list);
	cmd_list = handle_cd(data, cmd_list, &flag);
	if (flag)
		return (cmd_list);
	cmd_list = handle_unset(data, cmd_list, &flag);
	if (flag)
		return (cmd_list);
	cmd_list = handle_heredoc(data, cmd_list);
	return (cmd_list);
}
