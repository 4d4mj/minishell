/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:00:31 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/08 12:45:12 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse(const char *str, va_list args)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == '%')
			count += ft_check(++str, args);
		else
		{
			ft_putchar_fd(*str, 1);
			count++;
		}
		str++;
	}
	return (count);
}
