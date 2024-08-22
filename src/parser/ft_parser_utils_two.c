/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:22 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/07 18:18:36 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_lexer_token(t_lexer *lexer_list, char *path)
{
	lexer_list->token = CMD;
	free(lexer_list->lexer_comp);
	lexer_list->lexer_comp = ft_strdup(path);
	free(lexer_list->path);
	lexer_list->path = ft_strdup(path);
	free(path);
}
