/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:55:12 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/28 23:59:56 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief Update the PWD and OLDPWD in the env variable
 * @param data The data structure
 * @param new_path The new path
 */
static void	ft_change_path(t_data *data, char *new_path)
{
	int	i;

	i = -1;
	ft_free(data->old_pwd);
	data->old_pwd = ft_strdup(data->pwd);
	ft_free(data->pwd);
	data->pwd = ft_strdup(new_path);
	while (ft_strlen(data->pwd) > 1
		&& data->pwd[ft_strlen(data->pwd) - 1] == '/')
		data->pwd[ft_strlen(data->pwd) - 1] = '\0';
	ft_free(new_path);
	while (data->envp[++i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
		{
			ft_free(data->envp[i]);
			data->envp[i] = ft_strjoin("PWD=", data->pwd);
		}
		else if (!ft_strncmp(data->envp[i], "OLDPWD=", 7) && data->old_pwd)
		{
			ft_free(data->envp[i]);
			data->envp[i] = ft_strjoin("OLDPWD=", data->old_pwd);
		}
	}
}

/**
 * @brief Get the parent directory
 * @param path The current path
 * @return The parent directory path
 */
static char	*get_parent_dir(const char *path)
{
	size_t	len;
	char	*parent;

	len = ft_strlen(path);
	while (len > 1 && path[len - 1] != '/')
		len--;
	if (len == 0)
	{
		ft_free((char *)path);
		return (ft_strdup("/"));
	}
	if (len > 1)
		len--;
	parent = ft_strndup(path, len);
	ft_free((char *)path);
	return (parent);
}

/**
 * @brief Helper function to construct the new path
 * @param base The base path
 * @param component The path component to append
 * @return The new constructed path
 */
static char	*construct_new_path(char *base, const char *component)
{
	char	*temp_path;
	char	*new_path;

	if (strlen(base) > 1)
		temp_path = ft_strjoin(base, "/");
	else
		temp_path = ft_strdup(base);
	new_path = ft_strjoin(temp_path, component);
	free(temp_path);
	free(base);
	return (new_path);
}

/**
 * @brief Check and construct the full path for cd command
 * @param data The data structure
 * @param path The input path
 * @param ret The initial return path (should be dynamically allocated)
 * @param i The index
 * @return The full path
 */
static char	*ft_cd_case(t_data *data, char *path, char *ret, int i)
{
	char	**components;

	components = ft_split(path, '/');
	if (path[0] == '/')
	{
		free(ret);
		ret = ft_strdup("/");
	}
	while (components[++i])
	{
		if (!strcmp(components[i], ".."))
			ret = get_parent_dir(ret);
		else if (components[i][0] == '~' && !i)
		{
			free(ret);
			ret = ft_strjoin(data->home, components[i] + 1);
		}
		else if (!strcmp(components[i], "."))
			continue ;
		else
			ret = construct_new_path(ret, components[i]);
	}
	ft_free_arr(components);
	return (ret);
}

void	ft_mini_cd(t_data *data, t_cmd *cmd_list)
{
	t_lexer	*lexer_list;
	char	*path;
	int		check;

	lexer_list = cmd_list->lexer_list->next;
	if (!lexer_list)
		return ;
	path = ft_cd_case(data, remove_quotes(lexer_list->lexer_comp), ft_strdup(data->pwd), -1);
	check = chdir(path);
	if (check)
	{
		free(path);
		ft_error_cd(lexer_list->lexer_comp, data);
		return ;
	}
	ft_change_path(data, path);
}
