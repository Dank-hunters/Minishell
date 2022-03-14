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

void	infork(int sig)
{
    if (sig == SIGINT)
	write(1, "\n", 1);
}

void	handle_signox(int sig)
{
    //	    dprintf(2, "%i\n", g_int[1]);
    if (g_int[1] && sig == SIGQUIT)
    {
	;
    }
    else if (sig == SIGINT)
    {
	if (g_int[1] == 0)
	{
	    rl_on_new_line();
	    rl_redisplay();
	    write(2, "  \b\b", 4);	    
	    ft_putstr("\n");
	    rl_on_new_line();
	    rl_replace_line("", 0);
	    rl_redisplay();
	}
	else
	    infork(sig);
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
