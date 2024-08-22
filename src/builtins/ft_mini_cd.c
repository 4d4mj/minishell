/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:34:37 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 05:24:14 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_directory(t_data *data, char *comp)
{
	int	len;

	len = ft_strlen(comp) - 1;
	if (!ft_strcmp(comp, "~"))
		return (ft_strdup(data->home));
	else if (!ft_strcmp(comp, ".."))
		return (ft_path_back(ft_strdup(data->pwd)));
	else if (!ft_strcmp(comp, "-"))
	{
		if (data->old_pwd)
			return (ft_strdup(data->old_pwd));
		return (ft_error_cd (comp, data, 1), NULL);
	}
	else if (!ft_strcmp(comp, "."))
		return (ft_strdup(data->pwd));
	else if (ft_check_if_root(comp))
		return (ft_strdup("/"));
	else if (!ft_strncmp(comp, "~", 1))
		return (ft_strjoin_modifiedd(data->home, ft_substr(comp, 1, len)));
	else
		return (ft_strdup(comp));
}

char	*ft_normalize_path(t_data *data, char *str)
{
	char	*new_path;
	char	**paths;
	int		len;

	if (!ft_strcmp (str, "/") || !ft_strcmp (str, "//"))
		return (str);
	new_path = ft_strdup("");
	paths = ft_split(str, '/');
	len = ft_arr_len(paths);
	new_path = ft_new_path(data, paths, new_path, len);
	ft_free_arr(paths);
	free(str);
	return (new_path);
}

void	ft_mini_cd(t_data *data, t_cmd *cmd_list)
{
	t_lexer	*lexer_list;
	char	*str;

	ft_clean_executed_command(data, cmd_list);
	lexer_list = cmd_list->lexer_list;
	if (lexer_list && lexer_list->next)
		ft_error_cd(NULL, data, 0);
	else
	{
		if (!lexer_list || (!lexer_list->lexer_comp
				&& lexer_list->token == ARG))
		{
			str = ft_strdup(data->home);
			ft_chdir(data, NULL, str);
		}
		else
		{
			str = ft_get_directory(data, lexer_list->lexer_comp);
			if (str)
				ft_chdir(data, lexer_list->lexer_comp, str);
		}
	}
	return ;
}
