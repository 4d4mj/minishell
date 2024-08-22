/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:36:40 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/19 12:26:12 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	char	*str;

	if (!format || *format == '\0')
		return (-1);
	str = ft_strdup(format);
	if (!str)
		return (-1);
	count = 0;
	va_start(args, format);
	count = ft_parse(str, args);
	va_end(args);
	free(str);
	return (count);
}
