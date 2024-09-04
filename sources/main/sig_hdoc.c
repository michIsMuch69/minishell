/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:22:15 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/04 10:29:40 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	event(void)
{
	return (0);
}

int	*give_ptr(int *interrupted)
{
	static int	*ptr;

	if (interrupted)
		ptr = interrupted;
	else
		return (ptr);
	return (NULL);
}

void	hdoc_routine(int sig)
{
	int	*interrupted;

	(void) sig;
	interrupted = give_ptr(NULL);
	rl_replace_line("", 0);
	*interrupted = 130;
	rl_done = 1;
}

void	init_sig_hdoc(int *interrupted)
{
	*interrupted = 0;
	give_ptr(interrupted);
	signal(SIGINT, hdoc_routine);
	rl_event_hook = event;
}
