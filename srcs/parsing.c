/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:02:27 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/09 20:20:05 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*nmalloc(void **var, int size)
{
	*var = malloc(sizeof(char) * size);
	if (!(*var))
		return (NULL);
	while (size--)
		((char *)(*var))[size] = 0;
	return (*var);
}

int	pre_pre_cut(t_cmd_lst *cmd_ctrl, char *line)
{
	int i;
	int	j;
	int	len;
	t_command	*chunk;

	chunk = create_chunk();
	cmd_ctrl->first = chunk;
	i = 0;
	while (line[i])
	{
		if (!chunk)
			return (0/*error(2, MEMALFAILED)*/);
		len = 0;
		while (line[i] && line[i++] != '|')
			len++;
		if (!nmalloc((void **)&(chunk->command), len + 1))
			return (0/*error(2, MEMALFAILED)*/);
		j = 0;
		while (len--)
			chunk->command[j++] = line[i - len];
		chunk = chunk->next;
		if (line[i])
			chunk = create_chunk();
	}
	return (1);
}

t_command	*parsing(char *line)
{
	t_cmd_lst	*cmd_ctrl;
	t_command	*aff;
	
	cmd_ctrl = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	if (!pre_pre_cut(cmd_ctrl, line))
		return (0);
	aff = cmd_ctrl->first;
	while (aff != NULL)
	{
		dprintf(1, "%s\n", aff->command);
		aff = aff->next;	
	}
	return (0);
}

//chart 
//
