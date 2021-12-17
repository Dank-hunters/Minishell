/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:04:46 by cguiot            #+#    #+#             */
/*   Updated: 2021/12/16 16:15:17 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_putstr(char *str)
{
	while(*str)
	{
		write(1, str++, 1);
	}
}

int	strcomp(char *need, char *key) //0 c est a bonne cle, 1 c est pas la bonne
{
	int i;

	i = 0;
	while (need[i])
	{
		if (need[i] != key[i])
			return (1);
		i++;
	}
	if (need[i] == '\0' && key[i] == '\0')
		return (0);
	return (1);
}

void	aff_key(t_lst *data, char *str) // affiche la cle demande,
{
	t_env	*env;
	int 	i;

	i = 0;
	env = data->first;
	while (env != NULL && strcomp(str, env->key) == 1)
		env = env->next;
	if (env != NULL && strcomp(str, env->key) == 0)
		dprintf(1, "%s\n", env->value);
	else
		dprintf(1, "je dois te la rajouter\n");
}

char *found_key(t_lst *data, char *key)
{
	t_env	*env;
	int		i;

	i = 0;
	env = data->first;
	while (key[i])
	{
		if (key[i] != env->key[i])
		{
			env = env->next;
			i = -1;
		}
		i++;
	}
	return(env->value);
}

t_env	*get_key(t_lst *data, char *key)
{
	t_env	*env;
	int		i;

	i = 0;
	env = data->first;
	while (key[i])
	{
		if (key[i] != env->key[i])
		{
			env = env->next;
			i = -1;
		}
		i++;
	}
	return(env);
}
