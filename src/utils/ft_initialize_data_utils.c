/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_data_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:43:35 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/08 17:26:48 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_question_dollar_env(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**create_new_envp(char **envp, char *str, int i, int j)
{
	char	**new_envp;
	int		len;

	len = ft_arr_len(envp);
	new_envp = calloc(len, sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (++i < len)
	{
		if (ft_strncmp(envp[i], str, 2) != 0)
		{
			new_envp[j] = strdup(envp[i]);
			if (!new_envp[j])
			{
				ft_free_arr(new_envp);
				return (NULL);
			}
			j++;
		}
	}
	new_envp[j] = (NULL);
	ft_free_arr(envp);
	return (new_envp);
}

char	**ft_check_if_question(char **envp)
{
	char	**new_env;

	if (!has_question_dollar_env(envp, "?=")
		&& !has_question_dollar_env(envp, "$="))
		return (envp);
	if (has_question_dollar_env(envp, "?="))
		new_env = create_new_envp(envp, "?=", -1, 0);
	if (has_question_dollar_env(envp, "$="))
		new_env = create_new_envp(envp, "$=", -1, 0);
	ft_free_arr(envp);
	return (new_env);
}
