/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:34:44 by cguiot            #+#    #+#             */
/*   Updated: 2022/03/09 16:03:20 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	echo(int fd, char **args)
{
    int	i;
    int	tirayn;

    i = 1;
    tirayn = 0;
    while (args[i] && !strcmp(args[i], "-n"))
    {
	tirayn = 1;
	i++;
    }
    while (args[i])
    {
	ft_putstr_fd(fd, args[i]);
	if (args[i + 1])
	    ft_putstr_fd(fd, " ");
	i++;
    }
    if (!tirayn)
	ft_putstr_fd(fd, "\n");
    return (1);
}

char	*new_pwd(char *value, char *path)
{
    int		i;
    char	*dest;
    int		u;

    u = 0;
    i = ft_strlen(value);
    i += ft_strlen(path);
    if (!(nmalloc((void **)&dest, i + 2)))
	return (0);
    while (value[u])
    {
	dest[u] = value[u];
	u++;
    }
    dest[u] = '/';
    u++;
    i = 0;
    while (path[i])
    {
	dest[u] = path[i];
	u++;
	i++;
	dest[u] = '\0';
    }
    return (dest);
}

int	cd(t_command *cmds, t_lst *data, char *path)
{
    t_env	*env;
    t_env	*tmp;

    env = data->first;
    if (chdir(path) == -1)
    {
	error(cmds, env, errno, 0);
	return (1);
    }
    env = get_key(data, "OLDPWD");
    tmp = get_key(data, "PWD");
    env->value = tmp->value;
    tmp->value = new_pwd(tmp->value, path);
    return (1);
}

int	expor(t_lst *data, char **args) // reparrer args multiples
{
    int	i;


    i = 1;
    while (args[i])
    {
	if (ft_strchr(args[i], '='))
	{
	    unset(data, args + i - 1, 0);
	    if ( data->last)
	    {
		data->last->next = create_env_elem(args[i]);
		data->last->next->prev = data->last;
		data->last = data->last->next;
	    }
	    else
		data->last = create_env_elem(args[i]);
	}
	i++;
    }
    return (1);
}

int	unset(t_lst *data, char **args, int test) // reparer args multiples
{
    t_env	*env;
    int	i;
    i = 1;
    while (args[i])
    {
	if (ft_strchr(args[i], '=') == 1 && test == 1)
	    return (0);
	env = get_key(data, args[i]);
	if (env)
		dprintf(1, "%s", env->key);
	if (env)
	{
	dprintf(1, "bite");
	    if (env == data->last)
		data->last = env->prev;
	    free(env->key);
	    free(env->value);
	    if (env->prev)
		(env->prev)->next = env->next;
	    if (env->next)
		(env->next)->prev = env->prev;
	}
	free(env);
	i++;
    }
    return (1);
}

int	env(t_lst *data, int ntm)
{
    t_env	*env;

    env = data->first;
    if (ntm == 0)
    {
	while (env != NULL)
	{
	    ft_putstr(env->key);
	    ft_putstr("=");
	    ft_putstr(env->value);
	    ft_putstr("\n");
	    env = env->next;
	}
    }
    return (1);
}
