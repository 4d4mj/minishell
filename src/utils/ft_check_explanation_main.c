/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_explanation_main.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:25:58 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 12:09:32 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_explanation(t_data *data)
{
	char	*readline;
	t_lexer	*lexer_list;

	lexer_list = data->lexer_list;
	readline = data->lexer_list->lexer_comp;
	if (readline && readline[0] == '!' && readline[1] == '\0')
	{
		if (readline[1] == '\0' && lexer_list->next == NULL)
		{
			data->exit_status = EXIT_FAILURE;
			ft_reset_data(data);
		}
		data->explanation = 1;
		ft_lexer_del_first(&data->lexer_list);
	}
}
