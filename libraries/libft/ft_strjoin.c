/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:48:35 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/11 10:07:45 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		pref_len;
	int		suf_len;
	int		i;

	pref_len = 0;
	suf_len = 0;
	i = -1;
	while (s1 && s1[pref_len] != '\0')
		pref_len++;
	while (s2 && s2[suf_len] != '\0')
		suf_len++;
	dest = (char *)malloc((pref_len + suf_len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[++i] != '\0')
		dest[i] = s1 [i];
	i = -1;
	while (s2 && s2[++i] != '\0')
		dest[pref_len + i] = s2[i];
	if (!s2)
		i = 0;
	dest[pref_len + i] = '\0';
	return (dest);
}
