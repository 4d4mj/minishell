/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mini_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:57:13 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 16:26:37 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_char(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	while (str[++i])
	{
		if (str[i] != c)
			break ;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_strcmp_mini(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

void	ft_swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	ft_skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (is_whitespace(str[i + j]))
		j++;
	return (j);
}
