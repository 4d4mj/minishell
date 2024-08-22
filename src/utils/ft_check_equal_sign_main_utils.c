/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_equal_sign_main_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:47:28 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 03:43:09 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_assignment_sign(char *lexer_comp)
{
	if (!lexer_comp)
		return (0);
	if (ft_strchr(lexer_comp, '='))
		return (1);
	return (0);
}

t_lexer	*traverse_lexer_list(t_data *data, int *flag)
{
	t_lexer	*lexer_list;

	lexer_list = data->lexer_list;
	while (lexer_list && lexer_list->token != PIPE)
	{
		if (!has_assignment_sign(lexer_list->lexer_comp))
		{
			break ;
		}
		(*flag)++;
		lexer_list = lexer_list->next;
	}
	if (lexer_list && lexer_list->token == PIPE)
		(*flag)++;
	return (lexer_list);
}

void	remove_tokens(t_data *data, int flag)
{
	while (flag-- > 0)
		ft_lexer_del_first(&data->lexer_list);
}

int	ft_no_cmd_after(t_data *data, int flag)
{
	t_lexer	*lexer_list;

	lexer_list = traverse_lexer_list(data, &flag);
	if (lexer_list)
		remove_tokens(data, flag);
	return (flag);
}
