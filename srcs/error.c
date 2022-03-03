/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:37:49 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/16 17:44:15 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error(t_command *cmd_lst, t_env *env, int errnum, int exit)
{
	free_cmd_lst(cmd_lst);
    cmd_lst = 0;
    if (errnum < 30000)
        perror(strerror(errnum));
    else if (errnum == 30000)
        dprintf(2, "Syntax error\n");
    if (exit)
        exit_minishell(cmd_lst, env, 0, 1);
	return (0);
}

void    exit_minishell(t_command *cmd_lst, t_env *env, char **args, int ret)
{
    (void)args;
    free_cmd_lst(cmd_lst);
    free_env_lst(env);
    exit(ret);
}
