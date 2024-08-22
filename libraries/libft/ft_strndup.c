/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:43:14 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/30 08:44:50 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int len)
{
	char	*d;
	int		i;

	i = 0;
	if (!s || !*s)
		return (NULL);
	while (s[i] != '\0' && i < len)
		i++;
	i++;
	d = (char *)malloc((i * sizeof(char)));
	if (!d)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
