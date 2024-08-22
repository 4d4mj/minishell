/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:44:40 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 03:18:42 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_ifin_env(t_data *data, char *str)
{
	int		i;
	char	*var;
	char	*comp;

	i = 0;
	while (str && str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] != '\0')
		var = ft_substr(str, 0, i);
	else
		var = ft_strdup(str);
	if (str[i] == '=' && str[i + 1] != '\0')
		comp = ft_substr(str, i + 1, ft_strlen(str) - i);
	else if (str[i] == '=' && str[i + 1] == '\0')
		comp = NULL;
	else if (str[i] == '\0')
		comp = NULL;
	return (ft_check_if_exit_env(data, var, comp));
}

void	ft_add_env(t_data *data, char **str, int counter)
{
	char	**env_new;
	int		len;
	int		i;

	if (!(*str) || counter != 0 || (*str)[0] == '=')
		return ;
	if (ft_check_ifin_env(data, *str))
		return ;
	i = -1;
	len = ft_arr_len(data->envp);
	env_new = ft_calloc(sizeof(char *), len + 2);
	if (!env_new)
		return ;
	while (++i < len)
		env_new[i] = ft_strdup(data->envp[i]);
	i = 0;
	while (*str && (*str)[i] != '\0' && (*str)[i] != '=')
		i++;
	printf("i %d\n", i);
	ft_export_case(*str, env_new, len, i);
	ft_free_arr(data->envp);
	data->envp = ft_arrdup(env_new);
	ft_free_arr(env_new);
}

int	ft_check_equal_counter(char *str)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	if (!str)
		return (1);
	while (str && str[++i] != '\0')
	{
		if (str [i + 1] != '\0' && str[i] == '=' && str[i + 1] == '=')
			counter++;
	}
	return (counter);
}

int	ft_check_variables(t_data *data, t_lexer *lexer_list)
{
	int		check;
	int		counter;
	char	*str;

	check = 0;
	while (lexer_list)
	{
		str = ft_strdup(lexer_list->lexer_comp);
		counter = 0;
		if (str && ft_check_valid_variables(data, &str))
		{
			free(str);
			lexer_list = lexer_list->next;
			continue ;
		}
		if (str && (str[0] == '='))
			check = 1;
		counter = ft_check_equal_counter(str);
		if (counter != 0)
			check = counter;
		ft_add_env(data, &str, counter);
		free(str);
		lexer_list = lexer_list->next;
	}
	return (check);
}

void	ft_mini_export(t_data *data, t_cmd *cmd_list, int flag)
{
	t_lexer	*lexer_list;
	char	**env_variables;
	int		check;

	ft_clean_executed_command(data, cmd_list);
	lexer_list = cmd_list->lexer_list;
	if ((!lexer_list || (!lexer_list->lexer_comp
				&& lexer_list->token != ARG)) && flag == 0)
	{
		env_variables = ft_arrdup(data->envp);
		ft_qsort(env_variables);
		ft_free_arr(env_variables);
		exit (EXIT_SUCCESS);
	}
	check = ft_check_variables(data, lexer_list);
	if (check != 0 && flag == 0)
		ft_error_export(data, "", 0);
	else if (check != 0 && flag == 1)
		ft_error_env(data, "");
}
