/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:06:28 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/30 23:18:15 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*ft_lexer_new(char *readline, int type)
{
	t_lexer		*new_lexer;
	static int	i = 0;

	new_lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_lexer)
		return (0);
	new_lexer->lexer_comp = ft_strdup(readline);
	new_lexer->token = type;
	new_lexer->i = i++;
	new_lexer->next = NULL;
	new_lexer->prev = NULL;
	new_lexer->path = NULL;
	if (readline)
		free(readline);
	return (new_lexer);
}

void	ft_lexer_add_back(t_lexer **lexer_list, t_lexer *new_lexer)
{
	t_lexer	*current_lexer;

	current_lexer = *lexer_list;
	if (*lexer_list == NULL)
	{
		*lexer_list = new_lexer;
		return ;
	}
	while (current_lexer->next != NULL)
		current_lexer = current_lexer->next;
	current_lexer->next = new_lexer;
	new_lexer->prev = current_lexer;
}

int	ft_lexer_add(char *readline, int type, t_lexer **lexer_list)
{
	t_lexer	*new_lexer;
	char	*new_readline;

	if (type >= CMD && type <= MINICMD && readline
		&& (readline[0] == 34 || readline[0] == 39))
	{
		new_readline = ft_substr(readline, 1, ft_strlen(readline) - 2);
		free(readline);
		readline = new_readline;
	}
	new_lexer = ft_lexer_new(readline, type);
	if (!new_lexer)
		return (0);
	ft_lexer_add_back(lexer_list, new_lexer);
	return (1);
}

size_t	ft_lexer_len(t_lexer *lexer_list)
{
	size_t	i;

	i = 0;
	while (lexer_list)
	{
		i++;
		lexer_list = lexer_list->next;
	}
	return (i);
}
