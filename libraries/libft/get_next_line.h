/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:05:26 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/24 10:09:20 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

size_t	get_len(char *str);
char	*ft_remove_line(char *sline);
char	*get_next_line(int fd);
char	*get_target_line(char *sline);
char	*get_static_line(char *sline, int fd);
char	*update_static_line(char *sline, char *buffer, int *flag_new, size_t b);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

#endif