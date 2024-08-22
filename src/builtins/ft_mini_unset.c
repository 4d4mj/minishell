/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:45:01 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 05:27:18 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_validated_variable_unset(t_lexer *lexer)
{
	int		i;
	char	*var;

	i = 0;
	if (lexer->token == MINICMD)
		return (4);
	var = lexer->lexer_comp;
	if (!var || ft_isdigit(var[i]))
		return (1);
	if (var[i] == '-')
		return (2);
	if (var[i] == '=' || var[i] == '+')
		return (3);
	while (var[i])
	{
		if (var[i] == 59)
			return (5);
		if (var[i] == '@' || var[i] == '~' || var[i] == '-' || var[i] == '.'
			|| var[i] == '\\' || var[i] == '{' || var[i] == '}' || var[i] == 47
			|| var[i] == '#' || var[i] == '*' || var[i] == '+' || var[i] == '='
			|| var[i] == '%' || var[i] == '?' || var[i] == '.')
			return (1);
		i++;
	}
	return (0);
}

void	ft_create_new_env(t_data *data, t_lexer *lexer_list,
		char **new_env, int *j)
{
	int		i;

	i = -1;
	while (data->envp[++i])
	{
		if (!(!ft_strncmp(data->envp[i], lexer_list->lexer_comp,
					ft_strlen(lexer_list->lexer_comp))
				&& (data->envp[i][ft_strlen(lexer_list->lexer_comp)] == '\0'
				|| data->envp[i][ft_strlen(lexer_list->lexer_comp)] == '=')))
		{
			new_env[++(*j)] = ft_strdup(data->envp[i]);
			if (new_env[*j] == NULL)
				return (ft_free_arr(new_env));
		}
	}
}

void	ft_remove_variables(t_data *data, t_lexer *lexer_list, int *i, int *j)
{
	char	**new_env;
	int		check;

	check = ft_check_validated_variable_unset(lexer_list);
	if (check)
		return (ft_error_unset(data, lexer_list->lexer_comp, check));
	while (data->envp[*i])
		(*i)++;
	new_env = ft_calloc(sizeof(char *), *i + 1);
	if (!new_env)
		return ;
	ft_create_new_env(data, lexer_list, new_env, j);
	ft_free_arr(data->envp);
	data->envp = new_env;
}

void	ft_get_var_name(t_lexer *lexer_list)
{
	int		i;
	char	*new_comp;

	i = -1;
	while (lexer_list->lexer_comp[++i])
	{
		if (lexer_list->lexer_comp[i] == '=')
			break ;
	}
	new_comp = ft_substr(lexer_list->lexer_comp, 0, i);
	free(lexer_list->lexer_comp);
	lexer_list->lexer_comp = new_comp;
}

void	ft_mini_unset(t_data *data, t_cmd *cmd_list, int flag)
{
	t_lexer	*lexer_list;
	int		i;
	int		j;

	if (flag == 0)
		ft_clean_executed_command(data, cmd_list);
	lexer_list = cmd_list->lexer_list;
	if (lexer_list && lexer_list->token == MINICMD && flag == 0)
	{
		ft_clean_executed_command(data, cmd_list);
		lexer_list = cmd_list->lexer_list;
	}
	if (!lexer_list)
		return ;
	while (lexer_list)
	{
		i = 0;
		j = -1;
		if (flag == 1)
			ft_get_var_name(lexer_list);
		ft_remove_variables(data, lexer_list, &i, &j);
		lexer_list = lexer_list->next;
	}
	return ;
}
