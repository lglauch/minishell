/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:55 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/19 16:04:13 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_ctrlc(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//handle free
}

void	handle_ctrl_backslash(int signal)
{
	(void)signal;
	write(1, "SIGQUIT received\n", 18);
}

void	signal_handler(void)
{
	signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, handle_ctrl_backslash);
}
