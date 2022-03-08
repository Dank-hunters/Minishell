/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:06:46 by lrichard          #+#    #+#             */
/*   Updated: 2022/03/02 19:06:50 by lrichard         ###   ########lyon.fr   */
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
	close(cmd->prev->fd[1]);
	if (dup2(cmd->prev->fd[0], STDIN_FILENO) == -1 || \
		dup2(cmd->fd[1], STDOUT_FILENO) == -1)
	    return (0);
	close(cmd->prev->fd[0]);
    }
    else
    {
	close(cmd->prev->fd[1]);
	if (dup2(cmd->prev->fd[0], STDIN_FILENO) == -1)
	    return (0);
	close(cmd->prev->fd[0]);
    }
    if (cmd->prev || cmd->next)
      close(cmd->fd[0]);
    if (cmd->prev || cmd->next)
      close(cmd->fd[1]);
    return (1);
}

int	free_tmp(char *tmp)
{
   free(tmp);
   return (0);
}

char	*fif(char *tmp)
{
    return (tmp);
}

int	exec_fork(t_command *cmd_lst, char **path, char **envp, int i)
{
    int	 joined;
    char *tmp;

    tmp = cmd_lst->command;
    while (path[i])
    {
	joined = 0;
	if (!ft_strchr(cmd_lst->command, '/'))
	{
	    if (!fif(tmp = ft_strjoin(path[i], cmd_lst->command, 0, 0)))
		return (free_tmp(tmp));
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
    return (0);
}

int is_builtin_and_exec_builtin(t_command *cmd, t_lst *envv, int ret, int fd)
{
    if (cmd->redir_in_fd)
	fd = cmd->redir_in_fd;
    if (!ft_strcmp(cmd->command, "cd"))
	ret = cd(envv, cmd->args[1]);
    else if (!ft_strcmp(cmd->command, "echo"))
	ret = echo(fd, cmd->args);
    else if (!ft_strcmp(cmd->command, "env"))
	ret = env(envv, 0); // revoir
    else if (!ft_strcmp(cmd->command, "unset"))
	ret = unset(envv, cmd->args[1]); // args multiples
    else if (!ft_strcmp(cmd->command, "pwd"))
	aff_key(envv, "PWD");
    else if (!ft_strcmp(cmd->command, "export"))
	ret = expor(envv, cmd->args[1]); // args multplies
    else
	return (0);
    exit((ret == 0));
    return (0);
}

int	pre_fork(t_command *cmd, char **path, char **envp)
{
	if (!dup_des_trucs(cmd))
	    return (0);
	if (cmd->redir_in_fd && dup2(cmd->redir_in_fd, STDIN_FILENO) == -1 && close(cmd->redir_in_fd) )
	    return (0);
	if (cmd->redir_out_fd && dup2(cmd->redir_out_fd, STDOUT_FILENO) == -1  && close(cmd->redir_out_fd))
	    return (0);
	if (!exec_fork(cmd, path, envp, 0))
	    return (0);
	return (1);
}

int execute(t_command *cmd, char **path, t_lst *env, int *thefinalpid)
{
    int		i;
    int		pid;
    char    **envp;

    envp = rebuild_envp(env);
    if (!envp || ((cmd->next || cmd->prev) && pipe(cmd->fd) == -1))
	return (0);
    cmd->args[0] = cmd->command;
    pid = fork();
    if (pid == 0 && !is_builtin_and_exec_builtin(cmd, env, 0, 1) && \
	!pre_fork(cmd, path, envp))
    {
	dprintf(2, "mabite");
	error(cmd, 0, errno, 1);

    }else if (pid == -1)
	return (0);
    else if (!cmd->next)
	*thefinalpid = pid;
    if (cmd->next || cmd->prev)
	close(cmd->fd[1]);
    if (cmd->prev)
	close(cmd->prev->fd[0]);
    i = 0;
    while (envp[i])
	free(envp[i++]);
    free(envp);
    return (1);
}
