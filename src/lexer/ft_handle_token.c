/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:07:32 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/11 08:42:54 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_token(int c)
{
	static int	token_arr[5][2] = {
	{'|', PIPE},
	{'>', TRUNC},
	{'<', INPUT},
	};
	int			i;

	i = 0;
	while (i < 5)
	{
		if (token_arr[i][0] == c)
			return (token_arr[i][1]);
		i++;
	}
	return (0);
}

int	ft_helper_add(int type, t_lexer **lexer_list)
{
	if (!ft_lexer_add(NULL, type, lexer_list))
		return (-1);
	return (2);
}

int	ft_handle_token(t_data *data, int index, t_lexer **lexer_list)
{
	int	type;

	type = ft_check_token(data->readline[index]);
	if (type == TRUNC && ft_check_token(data->readline[index + 1]) == TRUNC)
		return (ft_helper_add(APPEND, lexer_list));
	else if (type == INPUT
		&& ft_check_token(data->readline[index + 1]) == INPUT)
		return (ft_helper_add(HEREDOC, lexer_list));
	else if (type)
	{
		if (!ft_lexer_add(NULL, type, lexer_list))
			return (-1);
		return (1);
	}
	return (0);
}
