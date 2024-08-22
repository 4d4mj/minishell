/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:24 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:44 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int x, size_t n)
{
	size_t			i;
	unsigned char	*char_ptr;

	char_ptr = ptr;
	i = 0;
	while (i < n)
	{
		char_ptr[i] = (unsigned char)x;
		i++;
	}
	return (ptr);
}
