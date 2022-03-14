/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:37:49 by cguiot            #+#    #+#             */
/*   Updated: 2022/03/09 16:18:11 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error(t_command *cmd_lst, t_env *env, int errnum, int exit)
{
    if (errnum == 2)
    {
	if (cmd_lst->args[0] && !ft_strchr(cmd_lst->args[0], '/'))
	    dprintf(2, "Minishell-4.2: command not found: %s\n", cmd_lst->args[0]);
	else if (cmd_lst->args[0])
	    dprintf(2, "Minishell-4.2: %s: No such file or directory\n", cmd_lst->args[0]);
	else if (cmd_lst->redir_out_path && !cmd_lst->redir_out_fd)
	    dprintf(2, "%s: could not open file\n", cmd_lst->redir_out_path);
	else if (cmd_lst->redir_in_path && !cmd_lst->redir_in_fd)
	    dprintf(2, "%s: could not open file\n", cmd_lst->redir_in_path);
    }
    else if (errnum < 30000)
	perror("Error");
    else if (errnum == 30000)
	dprintf(2, "Syntax error\n");
    else if (errnum == 30001)
	dprintf(2, "Minishell does not take args\n");
    if (exit)
	exiit(cmd_lst, env, 0, 1);
    return (0);
}

int	exiit(t_command *cmd_lst, t_env *env, char **args, \
	unsigned long long int ret)
{
    if (args && args[1])
    {
	ret = ft_atoi_custom(args[1]);
	if (ret == 9223372036854775808ULL)
	{
	    dprintf(2, "Minishell-4.2: exit: %s: numeric argument required\n", \
		    args[1]);
	    free_cmd_lst(cmd_lst);
	    free_env_lst(env);
	    exit(255);
	}
	else if (args[2])
	{
	    dprintf(2, "Minishell-4.2: exit: too many arguments\n");
	    return (1);
	}
    }
    free_cmd_lst(cmd_lst);
    free_env_lst(env);
    exit(ret);
}
