/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lift_mini_modified_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:28:39 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/21 18:48:53 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putstr_modified_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			i++;
			if (str[i])
				ft_putchar_fd(str[i], fd);
		}
		else
			write(fd, &str[i], 1);
		if (str[i])
			i++;
	}
}

void	ft_add_arr(t_cmd *cmd_list, char **arr, char *new_item, int flag)
{
	char	**new_arr;
	int		len;
	int		i;

	i = -1;
	len = 0;
	if (arr)
		len = ft_arr_len(arr);
	new_arr = ft_calloc(sizeof(char *), len + 2);
	if (!new_arr)
		return ;
	while (arr && arr[++i])
		new_arr[i] = ft_strdup(arr[i]);
	new_arr[len] = ft_strdup(new_item);
	new_arr[len + 1] = NULL;
	ft_free_arr(arr);
	if (flag == 1)
		cmd_list->input_file = ft_arrdup(new_arr);
	else if (flag == 0)
		cmd_list->output_file = ft_arrdup(new_arr);
	else if (flag == 2)
		cmd_list->heredoc = ft_arrdup(new_arr);
	ft_free_arr(new_arr);
}
