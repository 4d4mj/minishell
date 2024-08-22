/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_equal_sign_main.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:34:00 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 03:43:14 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen_until_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	update_envp_variable(char *search_key, char *new_value, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(search_key, envp[i], ft_strlen_until_equal(envp[i]))
			&& ft_strlen(search_key) - 1 == ft_strlen_until_equal(envp[i]))
		{
			printf("updated envp[i] %s\n", envp[i]);
			if (new_value != NULL)
			{
				free(envp[i]);
				envp[i] = ft_strjoin(search_key, new_value);
			}
		}
		i++;
	}
}

int	ft_check_if_exit_env(t_data *data, char *var, char *comp)
{
	char	*search_key;
	char	*env_key;
	t_env	*env_list;
	int		flag;

	flag = 0;
	env_list = data->env_list;
	search_key = ft_strjoin("$", var);
	env_key = ft_strjoin(var, "=");
	while (env_list)
	{
		if (!ft_strcmp(search_key, env_list->env_var))
		{
			flag = 1;
			if (comp != NULL)
			{
				free(data->env_list->env_comp);
				data->env_list->env_comp = ft_strdup(comp);
				update_envp_variable(env_key, comp, data->envp);
			}
		}
		env_list = env_list->next;
	}
	ft_free_four(var, comp, search_key, env_key);
	return (flag);
}

void	ft_export_exit_change(t_data *data)
{
	t_lexer	*lexer_list;
	char	*var;
	char	*comp;
	int		i;

	lexer_list = data->lexer_list;
	while (lexer_list)
	{
		i = 0;
		if (lexer_list->lexer_comp[i] != '=')
		{
			while (lexer_list->lexer_comp[i] != '\0'
				&& lexer_list->lexer_comp[i] != '=')
				i++;
			if (lexer_list->lexer_comp[i] != '\0')
			{
				var = ft_substr(lexer_list->lexer_comp, 0, i);
				comp = ft_substr(lexer_list->lexer_comp, i + 1,
						ft_strlen(lexer_list->lexer_comp) - i);
				ft_check_if_exit_env(data, var, comp);
			}
		}
		ft_lexer_del_first(&data->lexer_list);
		lexer_list = data->lexer_list;
	}
}

void	ft_check_equal_sign(t_data *data, int i, int counter)
{
	char	*line;

	if (ft_no_cmd_after(data, 0))
	{
		line = data->lexer_list->lexer_comp;
		if (line && ft_isalpha(line[0]))
		{
			while (line[++i])
			{
				if (line [i + 1] && line[i] == '=' && line[i + 1] != '=')
					counter++;
				else if (line[i + 1] && line[i] == '=' && line[i + 1] == '=')
				{
					counter = 0;
					break ;
				}
				else if (line[i + 1] == '\0' && line[i - 1] != '='
					&& line[i] == '=')
					counter++;
			}
			if (counter > 0)
				ft_export_exit_change(data);
		}
	}
}
