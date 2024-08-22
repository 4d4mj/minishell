/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:25:51 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/08 11:37:58 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_sprint(va_list args)
{
	char	*arg;
	int		count;

	count = 0;
	arg = va_arg(args, char *);
	if (arg == NULL)
	{
		ft_putstr_fd ("(null)", 1);
		return (6);
	}
	while (*arg != '\0')
	{
		ft_putchar_fd(*arg, 1);
		count++;
		arg++;
	}
	return (count);
}
