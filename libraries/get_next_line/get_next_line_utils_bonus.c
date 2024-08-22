/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:13:52 by akaterji          #+#    #+#             */
/*   Updated: 2024/06/20 18:38:30 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*allocate_and_initialize(char *sline, char *buffer)
{
	if (!sline && buffer)
	{
		sline = malloc(sizeof(char));
		if (!sline)
			return (NULL);
		sline[0] = '\0';
	}
	return (sline);
}

void	copy_data(char *new_sline, char *sline)
{
	size_t	i;

	i = 0;
	while (sline[i] != '\0')
	{
		new_sline[i] = sline[i];
		i++;
	}
	i = -1;
}

char	*update_static_line(char *sline, char *buffer, int *f_new, size_t lbuf)
{
	char	*new_sline;
	size_t	len_sline;
	size_t	i;

	sline = allocate_and_initialize(sline, buffer);
	if (!sline)
		return (NULL);
	len_sline = get_len(sline);
	new_sline = malloc(sizeof(char) * (len_sline + lbuf + 1));
	if (!new_sline)
		return (NULL);
	copy_data(new_sline, sline);
	i = -1;
	while (buffer[++i] != '\0')
	{
		new_sline[len_sline + i] = buffer[i];
		if (buffer[i] == '\n')
			*f_new = 1;
	}
	new_sline[len_sline + lbuf] = '\0';
	free(sline);
	return (new_sline);
}

char	*get_target_line(char *sline)
{
	char	*line;
	size_t	len_line;
	size_t	i;

	len_line = 0;
	if (!sline[len_line])
		return (NULL);
	while (sline[len_line] != '\n' && sline[len_line] != '\0')
		len_line++;
	line = malloc(sizeof(char) * (len_line + 2));
	if (!line)
		return (NULL);
	i = -1;
	while (++i < len_line && sline[i] != '\0')
		line[i] = sline[i];
	if (sline[i] == '\n')
	{
		line[i] = sline[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_remove_line(char *sline)
{
	char	*new_sline;
	int		len_sline;
	int		len_backn;
	size_t	len_new;
	size_t	i;

	len_backn = 0;
	while (sline[len_backn] != '\n' && sline[len_backn] != '\0')
		len_backn++;
	len_sline = get_len(sline);
	len_new = len_sline - len_backn;
	if (len_new > 0)
	{
		new_sline = malloc(sizeof(char) * (len_new + 1));
		if (!new_sline)
			return (NULL);
		i = 0;
		while (++i <= len_new)
			new_sline[i - 1] = sline[i + len_backn];
		new_sline[i - 1] = '\0';
	}
	else
		new_sline = NULL;
	free(sline);
	return (new_sline);
}
