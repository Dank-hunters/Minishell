/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:02:17 by cguiot            #+#    #+#             */
/*   Updated: 2022/03/09 16:27:27 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_lastcmdretvalue = 0;

char	**rebuild_envp(t_lst *env)
{
    int		i;
    int		len;
    char	**envp;
    t_env	*environment;

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

void	prompt_part_two(t_command *cmds, t_lst *data_env, int *thefinalpid)
{
    int			i;
    char		**path;

    path = ft_split(get_value(data_env, "PATH"), ':');
    if (!path)
	error(cmds, data_env->first, errno, 1);
    i = -1;
    while (path[++i])
	path[i] = ft_strjoin(path[i], "/", 1, 0);
    if (!cmds->prev && !cmds->next)
	i = exec_if_builtin(cmds, data_env, 0, 1);
    else
	while (cmds && execute(cmds, path, data_env, thefinalpid))
	    cmds = cmds->next;
    if (i == -1)
	error(cmds, data_env->first, errno, 1);
    i = 0;
    while (path[i])
	free(path[i++]);
    free(path);
}

void	prompt(t_cmd_lst *cmd_ctrl, t_lst *data_env, char *prt)
{
    int			status;
    int			thefinalpid;
    t_command		*cmds;

    while (1)
    {
	prt = readline("\033[36;03mMinishell-4.2 \033[33;03m$> \033[32;03m");
	if (prt && *prt)
	{
	    add_history(prt);
	    if (!parse_command(cmd_ctrl, data_env, prt))
		continue;
	    cmds = cmd_ctrl->first;
	    prompt_part_two(cmd_ctrl->first, data_env, &thefinalpid);
	    if (thefinalpid != -1)
		waitpid(thefinalpid, &status, 0);
	    free_cmd_lst(cmd_ctrl->first);
	}
    }
    free(prt);
}

void	init_shit(char **const envr)
{
    char		*prt;
    int			size;
    t_lst		*data_env;
    t_cmd_lst		cmd_ctrl;

    size = get_env_size(envr);
    prt = NULL;
    data_env = init_env_ctrl(envr);
    init_env_lst(data_env, envr, size);
    prompt(&cmd_ctrl, data_env, prt);
}

int	main(int ac, char **av, char **const envr)
{
    (void)av;
    if (ac == 1)
	init_shit(envr);
    else
	return (error(0, 0, 30001, 1));
    return (0);
}
