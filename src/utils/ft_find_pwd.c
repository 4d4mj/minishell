/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:39:45 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/29 22:34:57 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_find_pwd(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
			data->pwd = ft_substr(data->envp[i],
					4, ft_strlen(data->envp[i]) - 4);
		if (!ft_strncmp(data->envp[i], "OLDPWD=", 7))
			data->old_pwd = ft_substr(data->envp[i],
					7, ft_strlen(data->envp[i]) - 7);
		if (!ft_strncmp(data->envp[i], "HOME=", 5))
			data->home = ft_substr(data->envp[i],
					5, ft_strlen(data->envp[i]) - 5);
		i++;
	}
	if (data->pwd && !data->old_pwd)
		ft_arrdup_modified(data, &(*data->envp), "OLDPWD=");
}
