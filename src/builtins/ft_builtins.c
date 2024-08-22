/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:17:20 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 09:33:25 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_builtins_parent(t_data *data, t_cmd *cmd_list)
{
	char		*str;

	str = cmd_list->lexer_list->lexer_comp;
	if (str && cmd_list->lexer_list->token != HEREDOC)
	{
		if (!ft_strncmp("pwd", str, ft_strlen(str)))
			ft_mini_pwd(data, cmd_list);
		else if (!ft_strncmp("export", str, ft_strlen(str)))
			ft_mini_export(data, cmd_list, 0);
		else if (!ft_strncmp("echo", str, ft_strlen(str)))
			ft_mini_echo(data, cmd_list);
		else if (!ft_strncmp("env", str, ft_strlen(str)))
			ft_mini_env(data, cmd_list);
		else if (!ft_strncmp("exit", str, ft_strlen(str)))
			ft_mini_exit(data, cmd_list);
	}
}
