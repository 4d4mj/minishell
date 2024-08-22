/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_token_start_end_main.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:44:30 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 03:42:32 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_token_utils(int c)
{
	static int	token_arr[5][2] = {
	{'&', AND},
	{';', SEMI}
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

int	ft_check_token_start_end(char *line)
{
	int	len;
	int	type_e;

	type_e = 0;
	len = ft_strlen(line) - 1;
	if (len < 0)
		return (-1);
	if (len >= 0)
		type_e = ft_check_token(line[len]);
	if ((len && (ft_check_token(line[len - 1]) == TRUNC && type_e == TRUNC)))
		return (APPEND);
	else if ((len && (ft_check_token(line[len - 1]) == INPUT
				&& type_e == INPUT)))
		return (HEREDOC);
	else if ((ft_check_token(line[0]) == PIPE) || type_e == PIPE)
		return (PIPE);
	else if ((ft_check_token_utils(line[0]) == SEMI
			|| ft_check_token_utils(line[len]) == SEMI))
		return (SEMI);
	else if ((ft_check_token_utils(line[0]) == AND
			|| ft_check_token_utils(line[len]) == AND))
		return (AND);
	else if (type_e)
		return (type_e);
	return (0);
}
