/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:28:34 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/08 12:47:09 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_xprint(char c, va_list args)
{
	unsigned int	numhex;
	int				count;

	count = 0;
	numhex = va_arg(args, unsigned int);
	count = ft_num_hex_digits(numhex);
	if (c == 'x')
		ft_puthex_fd(numhex, 0, 1);
	else
		ft_puthex_fd(numhex, 1, 1);
	return (count);
}
