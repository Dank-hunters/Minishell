/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:13:13 by lrichard          #+#    #+#             */
/*   Updated: 2022/03/01 17:15:20 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int is_builtin_and_exec_builtin(t_command *cmd, t_lst *envv)
{
    if (!ft_strcmp(cmd->command, "cd"))
        cd(envv, cmd->args[1]);
    else if (!ft_strcmp(cmd->command, "echo"))
        ;//    echo();
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
    int     i;
    int     len;
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
    int     i;
    int     pid;
    int     status;
    char    **path;
    char    **envp;

    path = ft_split(get_value(env, "PATH"), ':');
    envp = rebuild_envp(env);
    if (!path || !envp)
        return (0); // errmsg alloc failed
    pid = fork();
    if (pid == 0)
    {
        if (is_builtin_and_exec_builtin(cmd_lst, env))
            return (0);
        i = 0;
        while (1)
        {
           if (!ft_strchr(cmd_lst->command, '/'))
            {
                cmd_lst->command = ft_strjoin(path[i], cmd_lst->command, 0, 0);
                //free(cmd_lst->command);
            }
           cmd_lst->args[0] = cmd_lst->command;
            if (execve(cmd_lst->args[0], cmd_lst->args, envp) == -1)
            {
                //if (!dealloc((void **)&cmd_lst->command, 0, ft_strlen(path[i])))
                  //  return (0);
                i++;
                free(cmd_lst->args[0]);
            }
        }
    }
   else // /!\ */
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            while (1)
                if (1)
                    write(1, "0\n", 2);
    }
    return (1);
}
