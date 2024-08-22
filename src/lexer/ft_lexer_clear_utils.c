/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_clear_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:57:54 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/11 17:50:46 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer_clear_list(t_lexer **lexer_list)
{
	t_lexer	*current_lexer;

	if (!lexer_list || !*lexer_list)
		return ;
	while (*lexer_list)
	{
		current_lexer = (*lexer_list)->next;
		if ((*lexer_list)->lexer_comp)
			free((*lexer_list)->lexer_comp);
		if ((*lexer_list)->path)
			free((*lexer_list)->path);
		free((*lexer_list));
		*lexer_list = current_lexer;
	}
	*lexer_list = NULL;
}

void	ft_lexer_del_first(t_lexer **lexer_list)
{
	t_lexer	*current_lexer;

	current_lexer = *lexer_list;
	*lexer_list = current_lexer->next;
	ft_lexer_clear_one(&current_lexer);
	if (*lexer_list)
		(*lexer_list)->prev = NULL;
}

t_lexer	*ft_lexer_clear_one(t_lexer **lexer_list)
{
	if ((*lexer_list)->lexer_comp)
	{
		free((*lexer_list)->lexer_comp);
		((*lexer_list)->lexer_comp) = NULL;
	}
	if ((*lexer_list)->path)
	{
		free((*lexer_list)->path);
		((*lexer_list)->path) = NULL;
	}
	free((*lexer_list));
	*lexer_list = NULL;
	return (NULL);
}

void	ft_lexer_del_one(t_lexer **lexer_list, int key)
{
	t_lexer	*current_lexer;
	t_lexer	*prev_lexer;
	t_lexer	*start_lexer;

	start_lexer = *lexer_list;
	current_lexer = start_lexer;
	if ((*lexer_list)->i == key)
	{
		ft_lexer_del_first(lexer_list);
		return ;
	}
	while (current_lexer && current_lexer->i != key)
	{
		prev_lexer = current_lexer;
		current_lexer = current_lexer->next;
	}
	if (current_lexer)
		prev_lexer->next = current_lexer->next;
	else
		prev_lexer->next = NULL;
	if (prev_lexer->next)
		prev_lexer->next->prev = prev_lexer;
	ft_lexer_clear_one(&current_lexer);
	*lexer_list = start_lexer;
}

void	ft_rotate_list_to_node(t_lexer **head, t_lexer *target_node)
{
	t_lexer	*current;
	t_lexer	*prev;
	t_lexer	*last;

	current = *head;
	prev = NULL;
	if (!head || !*head || !target_node)
		return ;
	while (current && current != target_node)
	{
		prev = current;
		current = current->next;
	}
	if (!current || current == *head)
		return ;
	if (prev)
		prev->next = NULL;
	last = current;
	while (last->next)
		last = last->next;
	last->next = *head;
	*head = current;
}
