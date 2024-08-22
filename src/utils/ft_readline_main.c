/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:13:58 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 16:13:51 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_trim_readline(t_data *data)
{
	char	*tmp;

	tmp = ft_strtrim(data->readline, " \t");
	if (data->readline)
	{
		free(data->readline);
		data->readline = NULL;
	}
	data->readline = ft_strdup(tmp);
	free(tmp);
	if (!data->readline)
		return (ft_reset_data(data));
}

char	*get_readline(t_data *data)
{
	char	*str;
	char	*tmp;
	char	*tmp2;

	if (data->pwd != NULL)
	{
		str = ft_strdup(data->pwd);
		if (!ft_strncmp(data->pwd, data->home, ft_strlen(data->home)))
		{
			tmp = ft_strjoin("~", &data->pwd[ft_strlen(data->home)]);
			free(str);
			str = ft_strdup(tmp);
			free(tmp);
		}
	}
	else
	{
		str = ft_strdup("");
	}
	tmp2 = ft_strjoin_modifiedd("\033[1;32mminishell:\033[1;34m", str);
	str = ft_strjoin(tmp2, "\033[0m$ ");
	free(tmp2);
	return (str);
}

int	ft_readline(t_data *data)
{
	char	*str;

	str = get_readline(data);
	data->readline = readline(str);
	free(str);
	if (data->readline == NULL)
	{
		ft_free_data(data);
		exit(EXIT_SUCCESS);
	}
	if (data->readline && (data->readline[0] == '\0'
			|| (data->readline[0] == 10 && data->readline[1] == '\0')))
		return (1);
	ft_check_signal(data);
	if (data->exit_status == 130 || data->exit_status == 131)
		ft_env_update(data);
	ft_trim_readline(data);
	add_history(data->readline);
	return (0);
}
