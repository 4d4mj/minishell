/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:29:43 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/11 16:54:55 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	uc;
	char			*tmp;

	tmp = NULL;
	uc = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == uc)
			tmp = (char *)s;
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (tmp);
}
