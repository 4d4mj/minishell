/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:38:55 by ajabado           #+#    #+#             */
/*   Updated: 2024/08/22 00:29:34 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_cmd	*ft_check_if_heredoc_alone(t_cmd *cmd_list)
// {
// 	if (!cmd_list->lexer_list->next->next)
// 	{
// 		// unlink(cmd_list->heredoc);
// 		return (cmd_list->next);
// 	}
// 	return (cmd_list);
// }

int	ft_is_dollar(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_change_variables(t_data *data, char *line, int i, int j)
{
	char	*new;
	char	*result;

	new = ft_strdup("");
	while (line && line[i] != '\0')
	{
		j = 0;
		result = NULL;
		while (line[i + j] != '\0' && line[i + j] != '$')
			j++;
		if (line[i + j] == '$' && line[i + j + 1] != '\0'
			&& (line[i + j + 1] == 34 || line[i + j + 1] == 39))
		{
			result = ft_strdup("$");
			i++;
		}
		else if (line[i + j] == '$')
			result = handle_dollar_sign(line, data->env_list, &i, &j);
		else
			result = handle_string(line, &i, &j);
		if (result)
			new = append_and_free(new, result);
	}
	return (new);
}
