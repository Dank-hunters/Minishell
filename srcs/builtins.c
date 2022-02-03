/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:34:44 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/03 17:50:27 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
void	echo(char *str, int fd, int i)// i = indice pour le -n, si 0 il es pas active
{
	if (i == 0)
		ft_putstr_fd(fd, str);
}
*/
int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
char	*new_pwd(char *value, char *path)
{
	int		i;
	char	*dest;
	int		u;

	u = 0;
	i = ft_strlen(value);
	i += ft_strlen(path);
	dest = malloc(sizeof(char) * i + 2);
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

	env = get_key(data, "OLDPWD");
	tmp = get_key(data, "PWD");
	env->value = tmp->value;
	tmp->value = new_pwd(tmp->value, path);
}

//void	pwd()


void expor(t_lst *data, char *path)
{
	data->last->next = creat_elem(path);
	data->last = data->last->next;
}


void	unset(t_lst *data, char *key)
{
	t_env	*env;

	env = get_key(data, key);
	env->set = 0;
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
	else
		ft_putstr("Sorry env no need arg\n");
	
}
