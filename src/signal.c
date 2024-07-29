/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:50:41 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/26 14:16:17 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	ft_sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	ft_sigint_handler(int sig)
{
	if (g_signal.in_heredoc)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (!g_signal.in_cmd)
	{
		g_signal.stop_heredoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	ft_init_signal(void)
{
	rl_event_hook = event;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
