/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_token_lexer_main.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:18:00 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/11 09:41:25 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_find_next_token(t_data *data, int i, int *flag)
{
	int	j;

	j = 0;
	*flag = 0;
	while (data->readline[i + j] != '\0'
		&& ft_check_token(data->readline[i + j]) != PIPE)
		j++;
	if (j == 0)
		ft_error_double_token(data, PIPE);
	if (data->readline[i + j] == PIPE)
	{
		*flag = 1;
		j--;
	}
	return (j);
}

char	*ft_trim_and_process_token(char *readline, int i, int j)
{
	char	*readline1;
	char	*trimmed_readline;

	readline1 = ft_substr(readline, i, j);
	trimmed_readline = ft_strtrim(readline1, " ");
	free(readline1);
	return (trimmed_readline);
}

void	ft_check_and_handle_errors(t_data *data, char *readline, int *token)
{
	*token = ft_check_token_start_end(readline);
	if (*token != 0)
		ft_error_double_token(data, *token);
}

void	ft_check_token_lexer(t_data *data)
{
	int		token;
	int		i;
	int		j;
	int		flag;
	char	*trimmed_readline;

	i = 0;
	while (data->readline[i] != '\0')
	{
		j = ft_find_next_token(data, i, &flag);
		trimmed_readline = ft_trim_and_process_token(data->readline, i, j);
		if (!trimmed_readline)
			printf("error");
		ft_check_and_handle_errors(data, trimmed_readline, &token);
		free(trimmed_readline);
		if (flag)
			j++;
		i += j;
		if (data->readline[i] != '\0')
			i++;
	}
}
