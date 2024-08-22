/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_is_directory_main.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:41:26 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 12:09:39 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_after_dir(t_data *data)
{
	int		i;
	char	*new_readline;

	i = 0;
	while (data->readline[i] != '\0' && !is_whitespace(data->readline[i]))
		i++;
	while (data->readline[i] != '\0' && is_whitespace(data->readline[i])
		&& data->readline[i] != '|')
		i++;
	if (data->readline[i] == '\0')
		ft_reset_data(data);
	if (data->readline[i + 1] != '\0' && data->readline[i] == '|')
		i++;
	if (data->readline[i] != '\0')
	{
		new_readline = ft_substr(data->readline, i,
				ft_strlen(data->readline) - i);
		free(data->readline);
		data->readline = new_readline;
	}
	else
		ft_reset_data(data);
}

void	ft_error_dir(t_data *data, char *comp, int type)
{
	if (type == IS_DIR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(comp, STDERR_FILENO);
		ft_putstr_fd(" : Is a directory\n", STDERR_FILENO);
		data->exit_status = IS_DIR;
	}
	else if (comp)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putstr_fd(comp, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		data->exit_status = NOT_DIR;
	}
	ft_check_after_dir(data);
}

int	ft_check_is_file(char *str)
{
	if (str)
	{
		if (!access(str, F_OK))
			return (2);
		if (!access(str, X_OK))
			return (1);
	}
	return (0);
}

int	ft_check_is_directory(char *str, t_data *data)
{
	struct stat	path_stat;

	if (str && (str[0] == '/' || str[0] == '.' || str[0] == '~'))
	{
		if (str[0] == '~' && str[1] == '\0')
		{
			free(data->lexer_list->lexer_comp);
			data->lexer_list->lexer_comp = ft_strdup(data->home);
			str = data->lexer_list->lexer_comp;
		}
		if (stat(str, &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
				return (ft_error_dir(data, str, IS_DIR), 1);
			else if (!access(str, X_OK) && !access(str, F_OK))
				return (0);
			else
				return (ft_error_dir(data, str, NOT_DIR), 1);
		}
		else
			perror("stat");
	}
	return (0);
}
