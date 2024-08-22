/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:00:53 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/13 18:58:36 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	src_len;
	unsigned int	dest_len;
	unsigned int	total_len;
	unsigned int	i;

	src_len = 0;
	dest_len = 0;
	i = 0;
	while (dest[dest_len] != '\0' && dest_len < size)
		dest_len++;
	while (src[src_len] != '\0')
		src_len++;
	total_len = src_len + dest_len;
	if (dest_len < size)
	{
		while (src[i] != '\0' && dest_len + i < size -1)
		{
			dest[dest_len + i] = src[i];
			i++;
		}
		dest[dest_len + i] = '\0';
	}
	return (total_len);
}
