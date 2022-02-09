/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:57:30 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/09 20:01:42 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


char *key(char *str)
{
	int	i;
	char *dest;

	i = 0;
	dest = NULL;
	while (str[i] && str[i] != '=')
		i++;
	dest = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] &&  str[i] != '=')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*value(char *str)
{
	int	i;
	int	u;
	char *dest;

	u = 0;
	i = 0;
	dest = NULL;
	while (str[u] && str[u] != '=')
		u++;
	if (str[u])
		u++;
	while (str[i])
		i++;
	dest = (char *)malloc(sizeof(char) * i - u + 1);
	i = 0;
	while (str[u])
	{
		dest[i] = str[u];
		i++;
		u++;
	}
	dest[i] = '\0';
	return (dest);
}

t_lst	init_env_ctrl(char **envr)
{
	t_lst	lst;

	lst.first = creat_elem(envr[0]);
	lst.size = 1;
	return (lst);
}

void	init_env_lst(t_lst *lst, char **envr, int size)
{
	t_env	*new;
	t_env	*current;
	int		i;

	i = 1;
	current = lst->first;
	while (i < size)
	{
		new = creat_elem(envr[i]);
		current->next = new;
		lst->last = current;
		current = current->next;
		i++;
	}
	//current->next = NULL;
}

void	*creat_elem(char *path)
{
	t_env	*new;

	new = malloc(sizeof(*new));
	new->key = key(path);
	new->value = value(path);
	new->set = 1;
	new->next = NULL;
	return (new);
}
