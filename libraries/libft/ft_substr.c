/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:19:06 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 16:25:15 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substr;
	size_t			strln;

	strln = ft_strlen(s);
	if (!s)
		return (0);
	if (start > strln)
		return (ft_strdup(""));
	if (len > strln - start)
		return (ft_strdup(s + start));
	i = 0;
	substr = (char *)malloc((len * sizeof(char)) + 1);
	if (!substr)
		return (0);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
