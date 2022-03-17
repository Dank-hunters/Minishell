/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:06:46 by lrichard          #+#    #+#             */
/*   Updated: 2022/03/09 17:47:37 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	dup_des_trucs(t_command *cmd)
{
	if (!cmd->prev)
	{
		if (cmd->next && dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			return (0);
	}
	else if (cmd->next)
	{
		if (dup2(cmd->prev->fd[0], STDIN_FILENO) == -1 || \
				dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			return (0);
		close(cmd->prev->fd[0]);
	}
	else
	{
		if (dup2(cmd->prev->fd[0], STDIN_FILENO) == -1)
			return (0);
		close(cmd->prev->fd[0]);
	}
	if (cmd->next)
		close(cmd->fd[0]);
	if (cmd->next)
		close(cmd->fd[1]);
	return (1);
}

int	is_builtin(t_command *cmd)
{
	if (!ft_strcmp(cmd->command, "cd") || !ft_strcmp(cmd->command, "echo") || !ft_strcmp(cmd->command, "env") || !ft_strcmp(cmd->command, "unset") || !ft_strcmp(cmd->command, "pwd") || !ft_strcmp(cmd->command, "export") || !strcmp(cmd->command, "exit"))
	    return (-1);
	return (0);
}

int	exec_if_builtin(t_command *cmd, t_lst *envv, int ret, int fd)
{
	if (cmd->redir_out_fd)
		fd = cmd->redir_out_fd;
	if (!ft_strcmp(cmd->command, "cd"))
		ret = cd(cmd, envv, cmd->args);
	else if (!ft_strcmp(cmd->command, "echo"))
		ret = echo(fd, cmd->args);
	else if (!ft_strcmp(cmd->command, "env"))
		ret = env(envv, 0); // revoir
	else if (!ft_strcmp(cmd->command, "unset"))
		ret = unset(cmd, envv, cmd->args, 1);
	else if (!ft_strcmp(cmd->command, "pwd"))
		aff_key(envv, "PWD");
	else if (!ft_strcmp(cmd->command, "export"))
		ret = expor(cmd, envv, cmd->args);
	else if (!strcmp(cmd->command, "exit"))
	{
	    exiit(cmd, envv->first, cmd->args, 0);
	    ret = 1;
	}
	else
		return (0);
	if (ret == 0)
	    return (-1);
	g_int[0] = 0;
	dprintf(1, "SETIT");
	return (ret);
}

int	free_tmp(char *tmp)
{
	free(tmp);
	return (0);
}

int	exec_cmd_part_two(t_command *cmd_lst, char **path, char **envp, int i)
{
	int		joined;
	char	*tmp;

	tmp = ft_strdup(cmd_lst->command, 0);
	while (path[i])
	{
		joined = 0;
		if (!ft_strchr(tmp, '/'))
		{
			tmp = ft_strjoin(path[i], tmp, 0, 1);
			if (!tmp)
				return (0);
			joined = 1;
		}
		if (execve(tmp, cmd_lst->args, envp) == -1)
		{
			if (joined && !dealloc((void **)&tmp, 0, \
						ft_strlen(path[i])))
				return (0);
			i++;
		}
		else
		    return (!free_tmp(tmp));
	}
	return (free_tmp(tmp));
}

int	exec_cmd(t_command *cmd, t_lst *env, char **path, char **envp)
{
    int ret;

	if (!dup_des_trucs(cmd))
		return (0);

	if (g_int[1] && cmd->redir_in_fd && dup2(cmd->redir_in_fd, STDIN_FILENO) == -1 && \
			close(cmd->redir_in_fd))
		return (0);

	if (g_int[1] && cmd->redir_out_fd &&
dup2(cmd->redir_out_fd, STDOUT_FILENO) == -1 && \
close(cmd->redir_out_fd))
		return (0);
	    ret = exec_if_builtin(cmd, env, 1, 1);
	if (ret == -1 || (ret == 0 && !exec_cmd_part_two(cmd, path, envp, 0)))
	    return (0);
	if (g_int[1])
	    exit(0);
	return (1);
}

int	execute(t_command *cmd, char **path, t_lst *env, int *thefinalpid)
{
	int		i;
	int		pid;
	char	**envp;

	if (cmd->next && pipe(cmd->fd) == -1)
		return (0);
	envp = rebuild_envp(env);
	if (!envp)
		return (0);
	pid = 0;
	if (cmd->next || cmd->prev || !is_builtin(cmd))
	{
	    g_int[1] = 1;
	    pid = fork();
	    if (pid == -1)
		return (0);
	}
	if (pid)
	    *thefinalpid = pid;
	else if (!exec_cmd(cmd, env, path, envp))
	    error(cmd, 0, errno, g_int[1]);
	if (cmd->next)
		close(cmd->fd[1]);
	if (cmd->prev)
		close(cmd->prev->fd[0]);
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (1);
}
