/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:02:17 by cguiot            #+#    #+#             */
/*   Updated: 2022/03/03 17:02:26 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int lastcmdretvalue = 0;

int	is_closed(char *str)
{
    if (str == NULL)
	return (1);
    if (str[0] != 'e')
	return (1);
    if (str[1] != 'x')
	return (1);
    if (str[2] != 'i')
	return (1);
    if (str[3] != 't')
	return (1);
    if (str[4] != '\0')
	return (1);
    else
    {
	dprintf(1, "exit\n");
	return (0);	
    }
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

int	prompt(char **envr)
{
    int			i;
    int			thefinalpid;
    int			status;
    char 		*prt;
    t_lst		*data_env;
    char	**path;
    t_cmd_lst	cmd_ctrl;
    t_command *cmds;
    int size;

    size = get_env_size(envr);
    prt = NULL;
    data_env = init_env_ctrl(envr);
    init_env_lst(data_env, envr, size);
    while (1)
    {
	prt = readline("\033[36;03mMinishell-4.2 \033[33;03m$> \033[32;03m");
	add_history(prt);
	if (prt && *prt)
	{
	    if (!parse_command(&cmd_ctrl, data_env, prt))
		continue;
	    cmds = cmd_ctrl.first;
	    while (cmds)
	    {
		path = ft_split(get_value(data_env, "PATH"), ':');
		if (!path)
		    return (error(cmd_ctrl.first, data_env->first, errno, 1));
		i = -1;
		while (path[++i])
		    path[i] = ft_strjoin(path[i], "/", 1, 0);
		execute(cmds, path, data_env, &thefinalpid);
		i = 0;
		 while (path[i])
		    free(path[i++]);
		free(path);
		cmds = cmds->next;
	    }
	    if (thefinalpid != -1)
		waitpid(thefinalpid, &status, 0);
	    // if (WIFEXITED(status))
	}
    }
    free(prt);
    return(0);
}

int main(int ac, char **av, char **const envr)
{
    (void)av;
    if (ac == 1)
    {
	prompt(envr);
    }
    else
	return (error(0, 0, 30001, 1));
    return (0);
}
