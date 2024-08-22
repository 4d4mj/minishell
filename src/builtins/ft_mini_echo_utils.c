/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_echo_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:03:06 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/04 12:13:29 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_env(char **array, int i, int j)
{
	char	c;
	int		flag;

	while (array[i])
	{
		flag = 1;
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (array[i][j])
		{
			c = array[i][j];
			if (c == '=' && flag)
			{
				ft_putstr_fd("=\"", 1);
				flag = 0;
			}
			else
				write(1, &c, 1);
			j++;
		}
		if (flag == 0)
			ft_putstr_fd("\"", 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	ft_qsort(char **array)
{
	int	num_elements;
	int	i;
	int	j;

	i = -1;
	j = -1;
	num_elements = 0;
	while (array[num_elements] != NULL)
		num_elements++;
	while (++i < num_elements - 1)
	{
		while (++j < num_elements - 1)
		{
			if (ft_strcmp_mini(array[j], array[j + 1]) > 0)
			{
				ft_swap_strings(&array[j], &array[j + 1]);
				j = -1;
			}
		}
	}
	ft_print_env(array, 0, 0);
}
