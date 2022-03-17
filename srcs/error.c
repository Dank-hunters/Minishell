/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:37:49 by cguiot            #+#    #+#             */
/*   Updated: 2022/03/17 20:49:34 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	setexitvalue(t_command *cmds, int errnum)
{
	if (errnum == 2)
	{
		if (cmds->args && \
				cmds->args[0] && !strcmp("cd", cmds->args[0]) && cmds->args[2])
			g_int[0] = 2;
		else if (cmds->args && \
				cmds->args[0] && !strcmp("cd", cmds->args[0]))
			g_int[0] = 2;
		else if (cmds->args && cmds->args[0] && !strcmp("unset", cmds->args[0]))
			g_int[0] = 2;
		else if (cmds->args && cmds->args[0] && !ft_strchr(cmds->args[0], '/'))
			g_int[0] = 127;
		else if (cmds->args && cmds->args[0])
			g_int[0] = 127;
	}
	else if (errnum == 13)
		g_int[0] = 126;
	else if (errnum == 30002)
		g_int[0] = 2;
	else if (errnum == 30003)
		g_int[0] = 2;
}

void	errnum_two(t_command *cmds, int *exit)
{
	if (cmds->args && \
			cmds->args[0] && !strcmp("cd", cmds->args[0]) && cmds->args[2])
		dprintf(2, "Minishell-4.2: cd: too many arguments\n");
	else if (cmds->args && \
			cmds->args[0] && !strcmp("cd", cmds->args[0]))
		dprintf(2, \
		"Minishell-4.2: cd: %s: No such file or directory\n", cmds->args[1]);
	else if (cmds->args && cmds->args[0] && !strcmp(cmds->args[0], "unset"))
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
	g_int[0] = 1;
	setexitvalue(cmds, errnum);
	if (errnum == 2)
	{
		errnum_two(cmds, &exit);
		if (exit)
			exiit(cmds, env, 0, g_int[0]);
		return (0);
	}
	else if (errnum < 30000)
		perror("Error");
	else if (errnum == 30000)
		ft_putstr_fd(2, "Syntax error\n");
	else if (errnum == 30002)
		ft_putstr_fd(2, "Minishell-4.2: cd: HOME not set\n");
	else if (errnum == 30001)
		ft_putstr_fd(2, "Minishell-4.2 does not take args\n");
	else if (errnum == 30003)
		ft_putstr_fd(2, "Minishell-4.2: export: invalid parameter name\n");
	if (exit)
		exiit(cmds, env, 0, g_int[0]);
	return (0);
}

void	exiit(t_command *cmds, t_env *env, char **args, \
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
			ft_putstr_fd(2, "Minishell-4.2: exit: too many arguments\n");
			return ;
		}
	}
	free_cmd_lst(cmds);
	free_env_lst(env);
	exit(ret);
}
