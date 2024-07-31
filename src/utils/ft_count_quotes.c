/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:36:29 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/30 23:10:19 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_find_matching_quote(char *line, int index, int *count, int type)
{
	int	i;

	i = index + 1;
	*count += 1;
	while (line && line[i] != '\0')
	{
		if (line[i - 1] == 92 && line[i] == type)
			;
		else if (line[i] == type)
			break ;
		i++;
	}
	if (line[i] == type)
		*count += 1;
	return (i - index);
}

int	ft_count_quotes(char *line)
{
	int	index;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	index = 0;
	while (line[index] != '\0')
	{
		if (line[index] == 34)
			index += ft_find_matching_quote(line, index, &d_quote, 34);
		if (line[index] == 39)
			index += ft_find_matching_quote(line, index, &s_quote, 39);
		if (line[index] != '\0')
			index++;
	}
	if ((d_quote > 0 && d_quote % 2 != 0) || (s_quote > 0 && s_quote % 2 != 0))
		return (0);
	return (1);
}
