/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:49:35 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/15 15:14:13 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr_fd(unsigned int n, int fd)
{
	char	digit;
	int		count;

	count = 0;
	if (n >= 10)
		count += ft_putunbr_fd(n / 10, fd);
	digit = '0' + (n % 10);
	ft_putchar_fd(digit, 1);
	count++;
	return (count);
}
