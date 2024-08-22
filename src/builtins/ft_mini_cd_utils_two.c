/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_cd_utils_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:51:20 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 05:23:15 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_change_to_specified_path(t_data *data, char *path, char *str)
{
	int		check;
	char	*new_path;

	check = chdir(str);
	if (check != 0)
	{
		ft_error_cd(path, data, 1);
		free(str);
	}
	else
	{
		printf("before %s\n", str);
		new_path = ft_normalize_path(data, str);
		printf("middle %s\n", new_path);
		ft_change_path(data, new_path);
		printf("after %s\n", data->pwd);
	}
}

void	ft_change_to_home_directory(t_data *data, char *str)
{
	int	check;

	ft_change_path(data, ft_strdup(data->home));
	check = chdir(str);
	if (check != 0)
	{
		ft_error_cd(NULL, data, 1);
		free(str);
	}
	free(str);
}

void	ft_chdir(t_data *data, char *path, char *str)
{
	if (path)
		ft_change_to_specified_path(data, path, str);
	else
		ft_change_to_home_directory(data, str);
}
