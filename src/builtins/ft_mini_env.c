/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:44:26 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 03:41:01 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_equal(t_data *data, t_cmd *cmd_list)
{
	t_lexer	*lexer;
	int		i;

	lexer = cmd_list->lexer_list->next;
	while (lexer)
	{
		i = -1;
		while (lexer->lexer_comp[++i])
		{
			if (lexer->lexer_comp[i] == '='
				|| lexer->token == TRUNC || lexer->token == APPEND)
				break ;
		}
		if (lexer->lexer_comp[i] == '\0'
			&& lexer->token != TRUNC && lexer->token != APPEND)
		{
			ft_error_env(data, lexer->lexer_comp);
			return (1);
		}
		lexer = lexer->next;
	}
	return (0);
}

void	ft_handle_cmd_list(t_data *data, t_cmd *cmd_list)
{
	if (!cmd_list->output_file && cmd_list->lexer_list
		&& cmd_list->lexer_list->next)
	{
		if (ft_check_equal(data, cmd_list))
			return ;
		ft_mini_export(data, cmd_list, 1);
		ft_print_environment_variables(data);
		ft_mini_unset(data, cmd_list, 1);
	}
	else
	{
		ft_clean_executed_command(data, cmd_list);
		ft_print_environment_variables(data);
	}
}

void	ft_remove_redundant_env_commands(t_data *data, t_cmd *cmd_list)
{
	int		i;
	t_lexer	*cur_lexer;

	cur_lexer = cmd_list->lexer_list;
	i = 0;
	while (cur_lexer)
	{
		if (cur_lexer->token == CMD)
			break ;
		i++;
		cur_lexer = cur_lexer->next;
	}
	if (cur_lexer)
	{
		while (i--)
			ft_clean_executed_command(data, cmd_list);
	}
	else if (cmd_list->lexer_list && cmd_list->lexer_list->next)
	{
		while (cmd_list->lexer_list && cmd_list->lexer_list->next
			&& !strcmp(cmd_list->lexer_list->lexer_comp, "env")
			&& !strcmp(cmd_list->lexer_list->next->lexer_comp, "env"))
			ft_clean_executed_command(data, cmd_list);
	}
}

void	ft_print_environment_variables(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->envp[i])
	{
		j = 0;
		while (data->envp[i][j] != '=' && data->envp[i][j] != '\0')
			j++;
		if (data->envp[i][j] != '\0' && ft_strncmp(data->envp[i], "$=", 2))
			ft_putendl_fd(data->envp[i], STDOUT_FILENO);
		i++;
	}
}

void	ft_mini_env(t_data *data, t_cmd *cmd_list)
{
	if (!cmd_list->output_file)
		ft_remove_redundant_env_commands(data, cmd_list);
	if (!ft_strcmp(cmd_list->lexer_list->lexer_comp, "env"))
	{
		ft_handle_cmd_list(data, cmd_list);
		exit (EXIT_SUCCESS);
	}
	return ;
}
