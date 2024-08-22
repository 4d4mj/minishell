/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:59:00 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/08 16:09:35 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(const char *str, va_list args)
{
	int		count;

	count = 0;
	if (*str == 's')
		return (ft_sprint (args));
	else if (*str == 'd' || *str == 'i')
		return (ft_diprint(args));
	else if (*str == 'c')
		return (ft_cprint(args));
	else if (*str == 'p')
		return (ft_pprint(args));
	else if (*str == 'u')
		return (ft_uprint(args));
	else if (*str == 'x' || *str == 'X')
		return (ft_xprint(*str, args));
	else if (*str == '%')
		return (ft_percentprint());
	return (count);
}
