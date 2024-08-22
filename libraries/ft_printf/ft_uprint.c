/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:27:36 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/15 16:23:20 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uprint(va_list args)
{
	unsigned int	unum;
	int				count;

	unum = va_arg(args, unsigned int);
	count = ft_unum_digits(unum);
	ft_putunbr_fd (unum, 1);
	return (count);
}
