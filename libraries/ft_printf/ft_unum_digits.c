/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unum_digits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:24:19 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/15 16:30:16 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unum_digits(unsigned int unum)
{
	int	count;

	count = 0;
	if (unum == 0)
		return (1);
	while (unum)
	{
		unum /= 10;
		count++;
	}
	return (count);
}
