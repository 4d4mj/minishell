/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:55:47 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/08 18:00:23 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

ssize_t	read_stat_file(char *buffer, size_t buffer_size)
{
	int		fd;
	ssize_t	bytes_read;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open /proc/self/stat");
		return (-1);
	}
	bytes_read = read(fd, buffer, buffer_size - 1);
	if (bytes_read == -1)
	{
		perror("Failed to read /proc/self/stat");
		close(fd);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	close(fd);
	return (bytes_read);
}

pid_t	extract_pid_from_buffer(const char *buffer)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = 0;
	while (ft_isdigit(buffer[i]) && buffer[i] != '\0')
	{
		pid = pid * 10 + (buffer[i] - '0');
		i++;
	}
	return (pid);
}

pid_t	ft_getpid(void)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;

	bytes_read = read_stat_file(buffer, sizeof(buffer));
	if (bytes_read == -1)
		return (-1);
	return (extract_pid_from_buffer(buffer));
}
