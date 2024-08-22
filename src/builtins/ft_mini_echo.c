/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:44:12 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/07 17:44:45 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putstr_modified_fd(char *str, int fd);

t_lexer	*ft_check_n(t_lexer *lexer_list, int *flag)
{
	char	*tmp;

	while (lexer_list)
	{
		tmp = ft_strdup(lexer_list->lexer_comp);
		if (tmp && (tmp[0] == 34 || tmp[0] == 39))
		{
			free(tmp);
			tmp = ft_substr(lexer_list->lexer_comp, 1,
					ft_strlen(lexer_list->lexer_comp) - 2);
		}
		if (tmp && ft_is_char(tmp, 'n'))
		{
			lexer_list = lexer_list->next;
			*flag = 1;
		}
		else
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	return (lexer_list);
}

void	ft_print_echo(t_data *data, t_lexer *lexer_list, int flag)
{
	t_lexer	*tmp_list;

	tmp_list = ft_check_n(lexer_list, &flag);
	if (!tmp_list && flag)
		ft_reset_data(data);
	while (tmp_list)
	{
		ft_putstr_modified_fd(tmp_list->lexer_comp, STDOUT_FILENO);
		if (tmp_list->next && tmp_list->lexer_comp)
			ft_putstr_fd(" ", STDOUT_FILENO);
		if (tmp_list->token >= TRUNC && tmp_list->token <= HEREDOC)
			tmp_list = tmp_list->next;
		tmp_list = tmp_list->next;
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	ft_mini_echo(t_data *data, t_cmd *cmd_list)
{
	t_lexer	*lexer_list;

	ft_clean_executed_command(data, cmd_list);
	lexer_list = cmd_list->lexer_list;
	ft_print_echo(data, lexer_list, 0);
	exit (EXIT_SUCCESS);
}
