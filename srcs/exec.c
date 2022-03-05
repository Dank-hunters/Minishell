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

int	exec_fork(t_command *cmd_lst, char **path, char **envp)
{
    int	 i;
    int	 joined;

    i = 0;
    while (path[i] && (cmd_lst->command)[0])
    {
	joined = 0;
	if (!ft_strchr(cmd_lst->command, '/'))
	{
	    path[i] = ft_strjoin(path[i], "/", 0, 0);
	    cmd_lst->command = ft_strjoin(path[i], cmd_lst->command, 0, 0);
	    joined = 1;
	}
	cmd_lst->args[0] = cmd_lst->command;
	if (execve(cmd_lst->args[0], cmd_lst->args, envp) == -1)
	{
	    if (joined && !dealloc((void **)&cmd_lst->command, 0, \
			ft_strlen(path[i])))
		return (0);
	    i++;
	}
    }
    exit(0);
}

int is_builtin_and_exec_builtin(t_command *cmd, t_lst *envv)
{
    if (!ft_strcmp(cmd->command, "cd"))
	cd(envv, cmd->args[1]);
    //  else if (!ft_strcmp(cmd->command, "echo"))
    //	;//	echo();
    else if (!ft_strcmp(cmd->command, "env"))
	env(envv, 0); // revoir
    else if (!ft_strcmp(cmd->command, "unset"))
	unset(envv, cmd->args[1]); // args multiples
    else if (!ft_strcmp(cmd->command, "pwd"))
	aff_key(envv, "PWD");
    else if (!ft_strcmp(cmd->command, "export"))
	expor(envv, cmd->args[1]); // args multplies
    else
	return (0);
    return (1);
}

int execute(t_command *cmd, char **path, char **envp, int *thefinalpid)
{
    int		pid;

    if ((cmd->next || cmd->prev) && pipe(cmd->fd) == -1)
	return (0);
    pid = fork();
    if (pid == 0 && !is_builtin_and_exec_builtin(cmd, env))
    {
	if (!dup_des_trucs(cmd))
	    return (0);
	if (cmd->redir_in_fd && dup2(cmd->redir_in_fd, STDIN_FILENO) == -1 && close(cmd->redir_in_fd) )
	    return (0);
	if (cmd->redir_out_fd && dup2(cmd->redir_out_fd, STDOUT_FILENO) == -1  && close(cmd->redir_out_fd))
	    return (0);
	if (!exec_fork(cmd, path, envp))
	    return (0);
    }
    else if (!cmd->next)
	*thefinalpid = pid;
    if (cmd->next || cmd->prev)
	close(cmd->fd[1]);
    if (cmd->prev)
	close(cmd->prev->fd[0]);
    free(path);
    return (1);
}
