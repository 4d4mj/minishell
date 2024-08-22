/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_backslash.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:23:38 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/21 17:18:23 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_after_backslash(char *tmp, char **new, char c, int *i)
{
	char	*new_value;

	if (c == '$' || c == 34 || c == 39 || c == '\\')
		return (1);
	new_value = ft_substr(tmp, *i -1, 2);
	if (new)
		*new = ft_strjoin_modified(*new, new_value);
	else
		*new = ft_strdup(new_value);
	free(new_value);
	if (tmp[*i] != '\0')
		(*i)++;
	return (0);
}

char	*ft_process_withbackslash(char *tmp, int *i, int *j, char *new)
{
	char	*value;
	char	*new_value;

	if (*i || *j)
		new = ft_substr(tmp, *i, *j);
	*i += *j + 1;
	if (ft_check_after_backslash(tmp, &new, tmp[*i], i))
	{
		*j = 1;
		while (tmp[*i + *j] != '\0' && tmp[*i + *j] != '$' && tmp[*i + *j] != 34
			&& tmp[*i + *j] != 39 && tmp[*i + *j] != '\\')
			(*j)++;
		value = ft_substr(tmp, *i, *j);
		*i += *j;
		if (new)
			new_value = ft_strjoin_modified(new, value);
		else
			new_value = ft_strdup(value);
		free(value);
		new = new_value;
		if (tmp[*i] == '$' || tmp[*i] == 34 || tmp[*i] == 39)
			(*i)--;
	}
	return (new);
}
