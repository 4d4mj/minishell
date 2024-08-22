/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:50:41 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/20 16:40:31 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigint_handler_beforecmd(int sig)
{
	g_signal_exit_status = sig;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigint_handler_incmd(int sig)
{
	g_signal_exit_status = sig;
	rl_replace_line("", 1);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_done = 1;
}

void	ft_signal_incmd(void)
{
	signal(SIGINT, ft_sigint_handler_incmd);
	signal(SIGQUIT, ft_sigint_handler_incmd);
}

void	ft_reset_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_check_signal(t_data *data)
{
	if (g_signal_exit_status == SIGINT)
	{
		data->exit_status = 130;
		g_signal_exit_status = 0;
	}
	else if (g_signal_exit_status == SIGQUIT)
	{
		data->exit_status = 131;
		g_signal_exit_status = 0;
	}
}
