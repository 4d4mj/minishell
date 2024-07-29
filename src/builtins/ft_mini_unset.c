/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:45:01 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/26 15:08:20 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_remove_variables(t_data *data, t_lexer *lexer_list, int *i, int *j)
{
	char	**new_env;

	while (data->envp[*i])
		(*i)++;
	new_env = ft_calloc(sizeof(char *), *i + 1);
	if (!new_env)
		return ;
	*i = -1;
	while (data->envp[++(*i)])
	{
		if (strncmp(data->envp[*i], lexer_list->lexer_comp,
				ft_strlen(lexer_list->lexer_comp)))
		{
			new_env[++(*j)] = ft_strdup(data->envp[*i]);
			if (new_env[*j] == NULL)
			{
				ft_free_arr(new_env);
				return ;
			}
		}
	}
	ft_free_arr(data->envp);
	data->envp = new_env;
}

void	ft_mini_unset(t_data *data, t_cmd *cmd_list)
{
	t_lexer	*lexer_list;
	int		i;
	int		j;
	int		check;

	check = 0;
	lexer_list = cmd_list->lexer_list->next;
	if (!lexer_list)
		return ;
	while (lexer_list)
	{
		i = 0;
		j = -1;
		ft_remove_variables(data, lexer_list, &i, &j);
		lexer_list = lexer_list->next;
		if (i == j)
		{
			check++;
			ft_error_export(lexer_list->lexer_comp);
		}
	}
	if (check)
		ft_reset_data(data);
}
