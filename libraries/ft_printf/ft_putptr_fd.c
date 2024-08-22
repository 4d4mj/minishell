/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:58:04 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/01 10:09:30 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr_fd(void *ptr, int fd)
{
	unsigned long	address;
	int				count;

	count = 0;
	address = (unsigned long)ptr;
	if (!address)
	{
		ft_putstr_fd ("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", fd);
	count += 2;
	count += ft_puthex_fd(address, 0, fd);
	return (count);
}
