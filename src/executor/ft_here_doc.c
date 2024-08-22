/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:37:03 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/22 01:01:22 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_heredoc_child(t_data *data, int fd, char *limiter)
{
	char	*line;
	char	*new_line;

	ft_reset_signal();
	line = readline("> ");
	while (line)
	{
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		if (ft_is_dollar(line, '$') && !data->quote_heredoc)
		{
			new_line = ft_change_variables(data, line, 0, 0);
			free(line);
			line = new_line;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(fd);
	exit(0);
}

int	ft_handle_heredoc_parent(t_data *data, pid_t pid, int fd, char *limiter)
{
	int	status;

	waitpid(pid, &status, 0);
	if (data->stop_heredoc)
	{
		close(fd);
		unlink(limiter);
		return (1);
	}
	return (0);
}

void	ft_here_doc(t_data *data, char *limiter)
{
	int		fd;
	pid_t	pid;

	fd = open(limiter, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		ft_handle_heredoc_child(data, fd, limiter);
	}
	else if (pid > 0)
	{
		if (ft_handle_heredoc_parent(data, pid, fd, limiter))
			return ;
	}
	else
	{
		perror("fork");
		return ;
	}
	return ;
}
