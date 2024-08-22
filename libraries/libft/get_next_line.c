/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:16:07 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/05 16:04:51 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_len(char *str)
{
	size_t		len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len] != 0)
		len++;
	return (len);
}

char	*free_and_null(char *buffer)
{
	free(buffer);
	return (NULL);
}

char	*get_static_line(char *sline, int fd)
{
	char	*buffer;
	int		read_bytes;
	int		flag_new;

	flag_new = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes == -1 || (!buffer && !sline))
		return (free_and_null(buffer));
	buffer[read_bytes] = '\0';
	while (read_bytes > 0 && !flag_new)
	{
		sline = update_static_line(sline, buffer, &flag_new, read_bytes);
		if (!flag_new)
		{
			read_bytes = read(fd, buffer, BUFFER_SIZE);
			if (read_bytes == -1)
				return (free_and_null(buffer));
			buffer[read_bytes] = '\0';
		}
	}
	free(buffer);
	return (sline);
}

char	*get_next_line(int fd)
{
	static char	*sline;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	sline = get_static_line(sline, fd);
	if (sline == NULL)
		return (NULL);
	line = get_target_line(sline);
	sline = ft_remove_line(sline);
	return (line);
}
