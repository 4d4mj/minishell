/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_reader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:58:41 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/04 12:51:54 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_read_words(char *readline, int index, t_lexer **lexer_list)
{
	int	j;
	int	nb_quote;

	j = 0;
	nb_quote = 0;
	while (readline[index + j] && !(ft_check_token(readline[index + j])))
	{
		if (readline[index + j] == 34 || readline[index + j] == 39)
			j += ft_find_matching_quote(readline, index + j,
					&nb_quote, readline[index + j]);
		else if (is_whitespace(readline[index + j]))
			break ;
		j++;
	}
	if (!ft_lexer_add(ft_substr(readline, index, j), 0, lexer_list))
		return (-1);
	return (j);
}

int	ft_lexer_reader(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->readline && data->readline[i])
	{
		j = 0;
		i += ft_skip_spaces(data->readline, i);
		if (ft_check_token(data->readline[i]))
			j = ft_handle_token(data, i, &data->lexer_list);
		else
			j = ft_read_words(data->readline, i, &data->lexer_list);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
