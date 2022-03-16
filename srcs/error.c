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

void	errnum_two(t_command *cmds, int *exit)
{
    if (cmds->args && \
	cmds->args[0] && !strcmp("cd", cmds->args[0]) && cmds->args[2])
	dprintf(2, "Minishell-4.2: cd: too many arguments\n");
    else if (cmds->args && \
	    cmds->args[0] && !strcmp("cd", cmds->args[0]))
	dprintf(2, \
	"Minishell-4.2: cd: %s: No such file or directory\n", cmds->args[1]);
    else if (cmds->args && cmds->args[0] && !strcmp("cd", cmds->args[0]))
	dprintf(2, "Minishell-4.2: unset: invalid parameter name\n");
    else if (cmds->args && cmds->args[0] && !ft_strchr(cmds->args[0], '/'))
	dprintf(2, "Minishell-4.2: %s: command not found\n", cmds->args[0]);
    else if (cmds->args && cmds->args[0])
	dprintf(2, \
	    "Minishell-4.2: %s: No such file or directory\n", cmds->args[0]);
    else if (cmds->redir_out_path && cmds->redir_out_fd == -1)
    {
	dprintf(2, "%s: could not open file\n", cmds->redir_out_path);
	*exit = 0;
    }
    else if (cmds->redir_in_path && cmds->redir_in_fd == -1)
    {
	dprintf(2, "%s: could not open file\n", cmds->redir_in_path);
	*exit = 0;
    }
}

int	error(t_command *cmds, t_env *env, int errnum, int exit)
{
    if (errnum == 2)
    {
	errnum_two(cmds, &exit);
	if (exit)
	    exiit(cmds, env, 0, 1);
	return (0);
    }
    else if (errnum < 30000)
	perror("Error");
    else if (errnum == 30000)
	dprintf(2, "Syntax error\n");
    else if (errnum == 30002)
	dprintf(2, "Minishell-4.2: cd: HOME not set\n");
    else if (errnum == 30001)
	dprintf(2, "Minishell does not take args\n");
    if (exit)
	exiit(cmds, env, 0, 1);
    return (0);
}

void    exiit(t_command *cmds, t_env *env, char **args, \
	unsigned long long int ret)
{
    if (args && args[1])
    {
	ret = ft_atoi_custom(args[1]);
	if (ret == 9223372036854775808ULL)
	{
	    dprintf(2, "Minishell-4.2: exit: %s: numeric argument required\n", \
		    args[1]);
	    return ;
	}
	if (args[2])
	{
	    dprintf(2, "Minishell-4.2: exit: too many arguments\n");
	    return ;
	}
    }
    free_cmd_lst(cmds);
    free_env_lst(env);
    exit(ret);
}
