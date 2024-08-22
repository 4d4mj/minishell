/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:51:22 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/01 10:02:13 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_fd(unsigned long num, int index, int fd)
{
	const char	*hex_digits1;
	const char	*hex_digits2;
	int			count;

	hex_digits1 = "0123456789abcdef";
	hex_digits2 = "0123456789ABCDEF";
	count = 0;
	if (index == 0)
	{
		if (num >= 16)
		{
			count += ft_puthex_fd(num / 16, index, fd);
		}
		write(fd, &hex_digits1[num % 16], 1);
		count++;
	}
	else
	{
		if (num >= 16)
			count += ft_puthex_fd(num / 16, index, fd);
		write(fd, &hex_digits2[num % 16], 1);
		count++;
	}
	return (count);
}
