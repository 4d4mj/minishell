/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 12:20:55 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/08 16:11:58 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include "../libft/libft.h"

int	ft_printf(const char *str, ...);
int	ft_xprint(char c, va_list args);
int	ft_uprint(va_list args);
int	ft_sprint(va_list args);
int	ft_putunbr_fd(unsigned int n, int fd);
int	ft_putptr_fd(void *ptr, int fd);
int	ft_puthex_fd(unsigned long num, int index, int fd);
int	ft_pprint(va_list args);
int	ft_percentprint(void);
int	ft_parse(const char *str, va_list args);
int	ft_num_hex_digits(unsigned int n);
int	ft_num_digits(int n);
int	ft_diprint(va_list args);
int	ft_cprint(va_list args);
int	ft_check(const char *str, va_list args);
int	ft_unum_digits(unsigned int unum);

#endif
