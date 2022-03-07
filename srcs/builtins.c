/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:34:44 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/10 22:56:59 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo(int fd, char **args)
{
    int i;
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
    while(value[u])
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
void	cd(t_lst *data, char *path)
{
    t_env *env;
    t_env *tmp;

    if (chdir(path) == -1)
    {
	dprintf(1, "mauvais dir\n\n\n");
	return ;
    }

    env = get_key(data, "OLDPWD");
    tmp = get_key(data, "PWD");
    env->value = tmp->value;
    tmp->value = new_pwd(tmp->value, path);
}

//void	pwd()


void expor(t_lst *data, char *path) // reparrer args multiples
{
    data->last->next = create_env_elem(path);
    data->last = data->last->next;
}


void	unset(t_lst *data, char *key) // reparer args multiples
{
    t_env	*env;

    env = get_key(data, key);
    if (env)
    {
	free(env->key);
	free(env->value);
	if (env->prev)
	    (env->prev)->next = env->next;
	if (env->next)
	    (env->next)->prev = env->prev;
    }
    free(env);
}



void	env(t_lst *data, int ntm)
{
    t_env	*env;

    env = data->first;
    if (ntm == 0)
    {
	while (env != NULL)
	{
	    if (env->set == 1)
	    {
		ft_putstr(env->key);
		ft_putstr("=");
		ft_putstr(env->value);
		ft_putstr("---");
		dprintf(1, "set :%d ", env->set);
		ft_putstr("\n");
	    }
	    env = env->next;
	}
    }

}
