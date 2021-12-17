/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:34:44 by cguiot            #+#    #+#             */
/*   Updated: 2021/12/16 17:21:35 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void	echo(char *str, int fd, int i)// i = indice pour le -n, si 0 il es pas active
{
	if (i == 0)
		ft_putstr_fd(fd, str);	
}

void	cd()


void	pwd()
*/

void expor(t_lst *data, char *path)
{
//	t_env	*env;
	
//	env = data->last; 
//	env = creat_elem(path);
//	dprintf(1, "%s\n", env->key);
//	data->last = env;

	data->last->next = creat_elem(path);
	data->last = data->last->next;
}


void	unset(t_lst *data, char *key)
{
	t_env	*env;

	env = get_key(data, key);
	env->set = 0;
}



void	env(t_lst *data)
{
	t_env	*env;

	env = data->first;
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
