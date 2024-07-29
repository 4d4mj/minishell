/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:19:13 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/26 09:19:33 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_strcpys(char *dst, const char *src)
{
	if (!src)
		return ;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strjoin_modified(char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = malloc((s1_len + s2_len + 1));
	if (!join)
		return (NULL);
	ft_strcpys(join, s1);
	ft_strcpys((join + s1_len), s2);
	if (s1)
		free(s1);
	return (join);
}
