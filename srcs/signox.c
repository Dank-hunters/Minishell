/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:25:41 by cguiot            #+#    #+#             */
/*   Updated: 2022/03/14 15:25:43 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_signox(int sig)
{

	if (sig == SIGQUIT)
	{
	;
	}
	else if (sig == SIGINT)
	{
	    rl_replace_line("", 1);

	}
	/*lse if (sig == SIGCONT)
	{
		dprintf(1, "CONTINUED ... BUT EXIT LOL\n");
		//exit(0);
	}*/


}

int	listen_signox()
{
	struct sigaction sga;

//	sigemptyset(&sga.sa_mask);
	sga.sa_flags = SA_RESTART;
	sga.sa_handler = &handle_signox;
	sigaction(SIGQUIT, &sga, 0);
	sigaction(SIGINT, &sga, 0);
	//sigaction(SIGCONT, &sga, 0);
	return 0;
}
