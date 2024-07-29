/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:44:12 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/29 22:29:31 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putstr_modified_fd(t_data *data, char *str, int fd);
int		ft_dollar_case(t_data *data, char *str, int index);

void	ft_print_without_quotes(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			i++;
			if (str[i])
				ft_putchar_fd(str[i], STDOUT_FILENO);
		}
		else if (str[i] == '$' && str[i + 1] != '\0')
			i = ft_dollar_case(data, str, i);
		else
			write(STDOUT_FILENO, &str[i], 1);
		if (str[i] != '\0')
			i++;
	}
}

int	ft_quote_case(t_data *data, char *str, int index, int type)
{
	int		count;
	int		new_index;
	char	*tmp;

	count = 0;
	new_index = ft_find_matching_quote(str, index, &count, type);
	if (count % 2 == 0)
	{
		tmp = ft_substr(str, index + 1, new_index -1);
		ft_print_without_quotes(data, tmp);
		free(tmp);
		return (new_index + index);
	}
	else
		write(STDOUT_FILENO, &str[index], 1);
	return (index + new_index);
}

int	ft_dollar_case(t_data *data, char *str, int index)
{
	int		new_index;
	char	*tmp;

	new_index = index + 1;
	while (str[new_index] != '\0')
	{
		if (str[new_index] && (str[new_index] == '$'
				|| is_whitespace(str[new_index]
					|| str[new_index] == 34 || str[new_index] == 39)))
			break ;
		new_index++;
	}
	tmp = ft_substr(str, index + 1, new_index -1);
	ft_get_variable(tmp, data->envp);
	return (new_index -1);
}

void	ft_putstr_modified_fd(t_data *data, char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			i++;
			if (str[i])
				ft_putchar_fd(str[i], fd);
		}
		else if ((str[i] == 34 || str[i] == 39))
			i = ft_quote_case(data, str, i, str[i]);
		else if (str[i] == '$' && str[i + 1] != '\0'
			&& (str[i + 1] != 34 && str[i + 1] != 39))
			i = ft_dollar_case(data, str, i);
		else
			write(fd, &str[i], 1);
		if (str[i])
			i++;
	}
}

int	ft_is_char(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	while (str[++i])
	{
		if (str[i] != c)
			break ;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

t_lexer	*ft_check_n(t_lexer *lexer_list, int *flag)
{
	char	*tmp;

	while (lexer_list)
	{
		tmp = ft_strdup(lexer_list->lexer_comp);
		if (tmp[0] == 34 || tmp[0] == 39)
		{
			free(tmp);
			tmp = ft_substr(lexer_list->lexer_comp, 1,
					ft_strlen(lexer_list->lexer_comp) - 2);
		}
		if (ft_is_char(tmp, 'n'))
		{
			lexer_list = lexer_list->next;
			*flag = 1;
		}
		else
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	return (lexer_list);
}

void	ft_print_echo(t_data *data, t_lexer *lexer_list, int flag)
{
	t_lexer	*tmp_list;

	tmp_list = ft_check_n(lexer_list, &flag);
	if (!tmp_list && flag)
		ft_reset_data(data);
	while (tmp_list)
	{
		ft_putstr_modified_fd(data, tmp_list->lexer_comp, STDOUT_FILENO);
		if (tmp_list->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
		tmp_list = tmp_list->next;
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}


int	ft_mini_echo(t_data *data, t_cmd *cmd_list)
{
	t_lexer	*lexer_list;

	lexer_list = cmd_list->lexer_list->next;
	ft_print_echo(data, lexer_list, 0);
	exit (EXIT_SUCCESS);
}
