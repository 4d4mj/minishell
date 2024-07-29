/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:17:20 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/29 22:28:54 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_builtins_child(t_data *data, t_cmd *cmd_list)
{
	char	*str;

	str = cmd_list->lexer_list->lexer_comp;
	if (str)
	{
		if (!ft_strncmp("echo", str, ft_strlen(str)))
			ft_mini_echo(data, cmd_list);
		else if (!ft_strncmp("env", str, ft_strlen(str)))
			ft_mini_env(data, cmd_list);
	}
	exit (EXIT_FAILURE);
}

void	ft_builtins_parent(t_data *data, t_cmd *cmd_list)
{
	char		*str;

	str = cmd_list->lexer_list->lexer_comp;
	if (str)
	{
		if (!ft_strncmp("cd", str, ft_strlen(str)))
			ft_mini_cd(data, cmd_list);
		else if (!ft_strncmp("pwd", str, ft_strlen(str)))
			ft_mini_pwd(data, cmd_list);
		else if (!ft_strncmp("export", str, ft_strlen(str)))
			ft_mini_export(data, cmd_list);
		else if (!ft_strncmp("unset", str, ft_strlen(str)))
			ft_mini_unset(data, cmd_list);
	}
	else if (cmd_list->lexer_list->token == HEREDOC)
	{
		ft_here_doc(cmd_list->input_file);
	}
}
