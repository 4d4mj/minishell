/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:32:00 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/21 17:31:01 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_str_digit(t_data *data, char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	if (!str)
		ft_error_exit_numeric(NULL, data);
	if (str[i] == '-' || str[i] == '+')
	{
		new_str = ft_substr(str, 1, ft_strlen(str));
		i++;
	}
	else
		new_str = ft_strdup(str);
	if (str[0] == '+' && ft_strcmp("9223372036854775807", new_str) < 0)
		return (free(new_str), 0);
	else if (str[0] == '-' && ft_strcmp("9223372036854775808", new_str) < 0)
		return (free(new_str), 0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (free(new_str), 0);
		i++;
	}
	return (free(new_str), 1);
}

int	ft_is_exit(t_data *data)
{
	t_cmd	*current_cmd;

	current_cmd = data->cmd_list;
	while (current_cmd)
	{
		if (current_cmd && !ft_strncmp(current_cmd->commands[0],
				"exit", ft_strlen("exit")))
		{
			if (current_cmd->next == NULL)
				return (2);
			else if (current_cmd->next != NULL)
				return (3);
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}

void	ft_mini_exit(t_data *data, t_cmd *cmd_list)
{
	t_lexer	*lexer_list;
	int		exit_code;

	exit_code = ft_is_exit(data);
	if (exit_code == 0)
		;
	else if (exit_code == 2)
	{
		lexer_list = cmd_list->lexer_list;
		if (ft_lexer_len(lexer_list) > 2
			&& ft_is_str_digit(data, lexer_list->next->lexer_comp))
			ft_error("exit: too many arguments\n", data);
		else if (lexer_list->next
			&& !ft_is_str_digit(data, lexer_list->next->lexer_comp))
			ft_error_exit_numeric(lexer_list->next->lexer_comp, data);
		else if (lexer_list)
			ft_exit_normal(data, lexer_list);
	}
	exit(EXIT_FAILURE);
}
