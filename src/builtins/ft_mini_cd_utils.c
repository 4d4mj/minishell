/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:54:52 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 05:11:12 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_change_path(t_data *data, char *new_path)
{
	ft_set_paths(data, new_path);
	if (!ft_getenv(data, "PWD="))
		ft_addenv(data, "PWD=", data->pwd);
	else
		ft_update_env(data, "PWD=", data->pwd);
	if (!ft_getenv(data, "OLDPWD="))
		ft_addenv(data, "OLDPWD=", data->old_pwd);
	else
		ft_update_env(data, "OLDPWD=", data->old_pwd);
	free(new_path);
}

char	*ft_path_back(char *str)
{
	size_t	i;
	size_t	len;
	char	*new_str;

	i = 0;
	len = 0;
	while (str && str[len])
	{
		if (str[len] == '/')
			i = len;
		len++;
	}
	if (i == 0)
		new_str = ft_strdup("/");
	else
		new_str = ft_substr(str, 0, i);
	free(str);
	return (new_str);
}

int	ft_check_if_current(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '.' && str[i + 1] == '\0')
		return (1);
	while (str[++i])
	{
		if (i % 2 == 0)
		{
			if (str[i] != '.')
				return (0);
		}
		if (i % 3 == 0)
		{
			if (str[i] != '/')
				return (0);
		}
	}
	return (1);
}

int	ft_check_if_root(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '/' && str[i + 1] == '\0')
		return (1);
	else if (str && str[i] != '/')
		return (0);
	while (str && str[++i])
	{
		if (str[i] != '/')
			return (0);
	}
	if (i == 2)
		return (0);
	return (1);
}

char	*ft_new_path(t_data *data, char **paths, char *new_path, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (!ft_strcmp(paths[i], "."))
			;
		else if (!ft_strcmp(paths[i], ".."))
			new_path = ft_path_back(new_path);
		else if (!i && !ft_strcmp(paths[i], "~"))
			new_path = ft_strdup_modified(new_path, data->home);
		else if (!ft_strcmp(paths[i], "home"))
			new_path = ft_strdup_modified(new_path, "/home");
		else
		{
			new_path = ft_strjoin_modified(new_path, "/");
			new_path = ft_strjoin_modified(new_path, paths[i]);
		}
	}
	return (new_path);
}
