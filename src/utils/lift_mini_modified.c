/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lift_mini_modified.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:05:05 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 16:29:41 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_four(char *s1, char *s2, char *s3, char *s4)
{
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	if (s3 != NULL)
		free(s3);
	if (s4 != NULL)
		free(s4);
}

char	*ft_strdup_modified(char *old, char *new)
{
	if (old)
		free(old);
	return (ft_strdup(new));
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
	ft_strcpy(join, s1);
	ft_strcpy((join + s1_len), s2);
	if (s1)
		free(s1);
	return (join);
}

char	*ft_strjoin_modifiedd(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = malloc((s1_len + s2_len + 1));
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy((join + s1_len), s2);
	if (s2)
		free(s2);
	return (join);
}

char	*ft_strjoin_modifiedsd(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = malloc((s1_len + s2_len + 1));
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy((join + s1_len), s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (join);
}
