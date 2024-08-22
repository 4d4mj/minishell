/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_export_utils_two.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:28:08 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 03:41:25 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export_case(char *str, char **env_new, int len, int i)
{
	if (str[i] == '\0')
		env_new[len] = ft_substr(str, 0, len);
	else
		env_new[len] = ft_strdup(str);
	printf("env_new[%d] = %s\n", len, env_new[len]);
	env_new[len + 1] = NULL;
}

void	ft_dot_case(char *str, int i, char **var)
{
	int	j;

	j = 0;
	free(*var);
	if (str[i] == ':')
	{
		while (str[i + j])
		{
			str[i + j] = '\0';
			j++;
		}
	}
}
