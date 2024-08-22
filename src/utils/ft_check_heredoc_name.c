/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_heredoc_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:18:50 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/08 15:44:23 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*find_heredoc_token(t_lexer *lexer_list)
{
	while (lexer_list)
	{
		if (lexer_list->token == HEREDOC)
			return (lexer_list);
		lexer_list = lexer_list->next;
	}
	return (NULL);
}

int	needs_modification(const char *lexer_comp)
{
	int	i;

	i = 0;
	while (lexer_comp[i])
	{
		if (lexer_comp[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	update_lexer_comp(t_lexer *lexer_list, int dollar_index)
{
	char	*new_comp;
	char	*original_comp;

	original_comp = lexer_list->lexer_comp;
	if (dollar_index >= 0)
	{
		new_comp = ft_substr(original_comp, 0, dollar_index);
		new_comp = ft_strjoin_modified(new_comp, "\\");
		new_comp = ft_strjoin_modifiedsd(new_comp, ft_substr(original_comp,
					dollar_index, ft_strlen(original_comp) - dollar_index));
		lexer_list->lexer_comp = ft_strdup_modified(original_comp, new_comp);
		free(new_comp);
	}
}

int	ft_check_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
	}
	return (0);
}

void	ft_check_heredoc_name(t_data *data)
{
	t_lexer	*lexer_list;
	int		dollar_index;

	lexer_list = find_heredoc_token(data->lexer_list);
	if (lexer_list && lexer_list->next && lexer_list->next->lexer_comp)
	{
		lexer_list = lexer_list->next;
		dollar_index = needs_modification(lexer_list->lexer_comp);
		data->quote_heredoc = ft_check_quotes(lexer_list->lexer_comp);
		if (dollar_index >= 0)
			update_lexer_comp(lexer_list, dollar_index);
	}
}
