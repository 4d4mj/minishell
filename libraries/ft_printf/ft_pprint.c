/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:26:45 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/15 15:13:20 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pprint(va_list args)
{
	void	*ptr;
	int		count;

	count = 0;
	ptr = va_arg(args, void *);
	count = ft_putptr_fd(ptr, 1);
	return (count);
}
