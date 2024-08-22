/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:23:30 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/19 11:44:16 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_diprint(va_list args)
{
	int	count;
	int	num;

	count = 0;
	num = va_arg(args, int);
	count = ft_num_digits(num);
	ft_putnbr_fd(num, 1);
	return (count);
}
