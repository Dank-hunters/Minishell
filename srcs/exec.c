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
		else
			break;
	}
	return (0);
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

char **rebuild_envp(t_lst *env)
{
	int	 i;
	int	 len;
	char **envp;
	t_env   *environment;

	if (!(nmalloc_2d(&envp, env->size + 1)))
		return (0);
	i = 0;
	environment = env->first;
	while (environment)
	{
		len = ft_strlen(environment->key) + ft_strlen(environment->value) + 1;
		if (!nmalloc((void **)&envp[i], len + 1))
			return (0);
		len = ft_strlen(environment->key);
		ft_strncpy(envp[i], environment->key, len);
		envp[i][len] = '=';
		ft_strncpy(envp[i] + len + 1, environment->value, \
				ft_strlen(environment->value));
		environment = environment->next;
		i++;
	}
	return (envp);
}

int execute(t_command *cmd_lst, t_lst *env)
{
	int	 pid;
	int	 status;
	char	**path;
	char	**envp;

	path = ft_split(get_value(env, "PATH"), ':');
	envp = rebuild_envp(env);
	if (!path || !envp)
		return (0); // errmsg alloc failed
	pid = fork();
	if (pid == 0 && !is_builtin_and_exec_builtin(cmd_lst, env))
		exec_fork(cmd_lst, path, envp);
	else if (pid != 0)// /!\ */
	{
		waitpid(pid, &status, 0);
		// if (WIFEXITED(status))

	}
	return (1);
}
