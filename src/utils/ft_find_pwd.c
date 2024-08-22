/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:39:45 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 05:26:14 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_find_pwd_check(t_data *data)
{
	if (!data->pwd)
		data->pwd = getcwd(NULL, 0);
	if (!data->old_pwd)
		data->old_pwd = getcwd(NULL, 0);
	if (!data->home)
		data->home = ft_strdup("/");
}

void	ft_find_pwd(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->envp[i])
		printf("EMPTY\n");
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "OLDPWD=", 7))
			data->old_pwd = ft_substr(data->envp[i],
					7, ft_strlen(data->envp[i]) - 7);
		if (!ft_strncmp(data->envp[i], "HOME=", 5))
			data->home = ft_substr(data->envp[i],
					5, ft_strlen(data->envp[i]) - 5);
		i++;
	}
	ft_find_pwd_check(data);
}
