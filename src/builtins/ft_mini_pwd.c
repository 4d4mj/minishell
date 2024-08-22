/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:44:52 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 05:27:33 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_pwd(char *pwd)
{
	char	*new_pwd;

	if (pwd)
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
	{
		new_pwd = getcwd(NULL, 0);
		ft_putendl_fd(new_pwd, STDOUT_FILENO);
		free(new_pwd);
	}
}

void	ft_mini_pwd(t_data *data, t_cmd *cmd_list)
{
	t_lexer	*lexer_list;
	int		flag;

	flag = 1;
	ft_clean_executed_command(data, cmd_list);
	lexer_list = cmd_list->lexer_list;
	if (cmd_list->output_file)
		;
	else if (lexer_list)
	{
		while (lexer_list)
		{
			if (lexer_list->lexer_comp
				&& lexer_list->lexer_comp[0] == '-')
			{
				ft_error_pwd(data, lexer_list->lexer_comp);
				flag = 0;
			}
			ft_clean_executed_command(data, cmd_list);
			lexer_list = cmd_list->lexer_list;
		}
	}
	if (flag)
		ft_print_pwd(data->pwd);
	exit (EXIT_SUCCESS);
}
