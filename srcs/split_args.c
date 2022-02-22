/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:49:21 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/22 18:49:23 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_arg(t_command *cmd_lst, int *i, int *y)
{
	int x;
	int j;
	int len;

	j = *i;
	
	while (*i && cmd_lst->command[(*i)] == ' ')
		(*i)++;
	if (!*i || !cmd_lst->command[(*i)])
		return (1);
	iter_through_word(cmd_lst->command, i);
	len = *i - j;	if (!nmalloc((void **)&(cmd_lst->args[*y]), sizeof(char) * (len + 1)))
		return (0);
	x = 0;
	while (j < *i)
		cmd_lst->args[*y][x++] = cmd_lst->command[j++];
	cmd_lst->args[*y][x] = 0;
	if (!dealloc((void **)&(cmd_lst->command), j - x, *i))
		return (0);
	*i = j - x;
	trim_spaces(&(cmd_lst->args[*y]));
	(*y)++;
	return (1);
}

void	iter_through_word(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '\'' && ++(*i))
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	else if (str[*i] == '"' && ++(*i))
		while (str[*i] && str[*i] != '"')
			(*i)++;
	else
		while (str[*i] && str[*i] != ' ')
			(*i)++;
	if (str[*i] == '\'' || str[*i] == '"')
		(*i)++;
}

int	argscount(char *str)
{
	int	i;
	int	argsn;

	i = 0;
	argsn = 0;
	while (str[i])
	{
		iter_through_word(str, &i);
		if (str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			argsn += (str[i] != 0);
		}
	}
	return (argsn);
}

int	split_args(t_command *cmd_lst, int i, int y)
{
	while (cmd_lst)
	{
		if (!nmalloc_2d((char ***)&(cmd_lst->args), \
				(argscount(cmd_lst->command) + 2)))
			return (0);
		cmd_lst->args[0] = cmd_lst->command;
		if (!argscount(cmd_lst->command))
		{
			if (!trim_spaces(&(cmd_lst->command)))
				return (0);
			cmd_lst = cmd_lst->next;
			continue;
		}
		i = 0;
		iter_through_word(cmd_lst->command, &i);
		y = 1;
		while (cmd_lst->command[i])
			if (!get_arg(cmd_lst, &i, &y))
				return (0);
		if (!trim_spaces(&(cmd_lst->command)))
			return (0);
		cmd_lst->args[0] = cmd_lst->command;
		cmd_lst = cmd_lst->next;
	}
	return (1);
}

