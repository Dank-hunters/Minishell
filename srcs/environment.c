/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:28:02 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/24 17:49:40 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_env_size(char **envr)
{
	int i;

	i = 0;
	while(envr[i])
		i++;
	return (i);
}

void	aff_key(t_lst *data, char *str) // affiche la cle demande,
{
	t_env	*env;
	int 	i;

	i = 0;
	env = data->first;
	while (env != NULL && ft_strcmp(str, env->key))
		env = env->next;
	if (env != NULL && !ft_strcmp(str, env->key))
		dprintf(1, "%s\n", env->value);
	else
		dprintf(1, "je dois te la rajouter\n");
}

char *get_value(t_lst *data, char *key)
{
	t_env	*env;
	int		i;

	i = 0;
	env = data->first;
	while (env && key[i])
	{
		if (key[i] != env->key[i])
		{
			env = env->next;
			i = -1;
		}
		i++;
	}
	if (env && ft_strlen(key) != ft_strlen(env->key))
		return (ft_strdup(""));
	if (env)
		return(env->value);
	else 
		return (ft_strdup(""));
}


t_env	*get_key(t_lst *data, char *key)
{
	t_env	*env;
	int		i;

	i = 0;
	env = data->first;
	while (env && key[i])
	{
		if (key[i] != env->key[i])
		{
			env = env->next;
			i = -1;
		}
		i++;
	}
	if (env && (ft_strlen(key) != ft_strlen(env->key) || env->set == 0))
		return (NULL);
	return(env);
}
