/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:19:16 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 03:05:21 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_variable_name(char *var, char *comp)
{
	int	i;

	i = 0;
	if ((var[i] == '=' || var[i] == '%') && var[i + 1] == '\0')
		return (ft_free_four(var, comp, NULL, NULL), 1);
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '/' || var[i] == '~' || var[i] == '-' || var[i] == '.'
			|| var[i] == '\\' || var[i] == '{' || var[i] == '}' || var[i]
			== '#' || var[i] == '*' || var[i] == '?' || var[i] == '@'
			|| (var[i] == '+' && var[i + 1] != '=' ))
			return (ft_free_four(var, comp, NULL, NULL), 1);
		i++;
	}
	return (0);
}

int	ft_check_exp_dot(char *str, char **var, int i, int *flag)
{
	int	j;

	j = 1;
	while (str[i + j] != '\0')
	{
		if (str[i + j] == '!' || str[i + j] == ':')
		{
			*var = ft_substr(str, i + j, ft_strlen(str) - i - j);
			if (str[i + j] == ':')
			{
				*flag = 0;
				break ;
			}
			else
			{
				*flag = 2;
				return (-1);
			}
		}
		j++;
	}
	ft_dot_case(str, i + j, var);
	return (j);
}

int	split_string(char *str, char **var, char **comp, int *flag)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!str)
		return (1);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		j = ft_check_exp_dot(str, var, i, flag);
		if (j < 0)
			return (1);
	}
	if (str[i + j] == '\0' && str[i] == '=')
	{
		*var = ft_substr(str, 0, i + 1);
		*comp = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	}
	else if (str[i + j] == '\0' && str[i + j -1] == '=')
		*var = ft_substr(str, 0, i);
	else
		*var = ft_strdup(str);
	return (0);
}

char	*modify_variable(t_data *data, char *var, char *comp, int *flag)
{
	char	*new_comp;
	char	*new_var;
	int		i;

	i = -1;
	new_comp = NULL;
	if (*flag == 1)
	{
		new_var = ft_substr(var, 0, ft_strlen(var) - 2);
		new_var = ft_strjoin_modified(new_var, "=");
		while (data->envp[++i])
		{
			if (!ft_strncmp(new_var, data->envp[i], ft_strlen(new_var)))
			{
				new_comp = ft_strjoin(comp, comp);
				break ;
			}
		}
		if (!new_comp)
			new_comp = ft_strdup(comp);
		new_var = ft_strjoin_modified(new_var, new_comp);
		free(new_comp);
		return (new_var);
	}
	return (NULL);
}

int	ft_check_valid_variables(t_data *data, char **str)
{
	char	*var;
	char	*comp;
	int		flag;
	char	*new_str;

	var = NULL;
	comp = NULL;
	flag = 0;
	new_str = NULL;
	if ((*str) && ft_isdigit((*str)[0]))
		return (ft_error_export(data, *str, 0), 1);
	if (split_string(*str, &var, &comp, &flag))
		return (ft_error_export(data, var, flag), free(var), 1);
	if (validate_variable_name(var, comp))
		return (ft_error_export(data, *str, 0), 1);
	if (strlen(var) > 1 && var[strlen(var) - 2] == '+'
		&& var[strlen(var) - 1] == '=')
		flag = 1;
	new_str = modify_variable(data, var, comp, &flag);
	if (new_str)
	{
		free(*str);
		*str = new_str;
	}
	return (ft_free_four(var, NULL, comp, NULL), 0);
}
