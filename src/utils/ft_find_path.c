/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:37:58 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/10 13:45:50 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup(""));
}

int	ft_find_path(t_data *data)
{
	char	*path;
	int		i;
	char	*tmp;

	path = ft_get_path(data->envp);
	if (path)
	{
		data->paths = ft_split(path, ':');
		i = 0;
		while (data->paths[i])
		{
			if (ft_strncmp(&data->paths[i][ft_strlen(data->paths[i]) - 1],
				"/", 1) != 0)
			{
				tmp = ft_strjoin(data->paths[i], "/");
				free(data->paths[i]);
				data->paths[i] = tmp;
			}
			i++;
		}
	}
	else
		data->paths = NULL;
	return (free(path), EXIT_SUCCESS);
}
