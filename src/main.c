/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:17:03 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 16:40:37 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal_exit_status;
void	ft_minishell_loop(t_data *data);

void	ft_reset_data(t_data *data)
{
	ft_free_data(data);
	ft_initialize_data(data);
	ft_minishell_loop(data);
}

void	ft_init_signal(void)
{
	signal(SIGINT, ft_sigint_handler_beforecmd);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_minishell_loop(t_data *data)
{
	ft_env_update(data);
	if (ft_readline(data))
		return (ft_reset_data(data));
	if (!ft_count_quotes(data->readline))
		return (ft_error("unable to find the next quote\n", data));
	ft_check_token_lexer(data);
	if (!ft_lexer_reader(data))
		return (ft_error("memory error: unable to assign memory\n", data));
	ft_check_heredoc_name(data);
	ft_check_quotes_in_string(data);
	ft_check_explanation(data);
	ft_check_equal_sign(data, 0, 0);
	if (!data->lexer_list)
		return (ft_reset_data(data));
	ft_check_if_empty(data);
	if (ft_check_is_directory(data->lexer_list->lexer_comp, data))
		return (ft_reset_data(data));
	ft_parser(data);
	ft_prepare_executor(data);
	ft_reset_data(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
		ft_error("This program does not accept arguments\n", NULL);
	data.exit_status = 0;
	ft_init(&data, ft_arrdup(envp));
	return (0);
}
