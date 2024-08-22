/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 08:43:00 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/31 09:01:46 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_in(const char s, const char *set)
{
	int	times;

	times = 0;
	while (*set)
	{
		if (s == *set)
			times++;
		set++;
	}
	return (times);
}
