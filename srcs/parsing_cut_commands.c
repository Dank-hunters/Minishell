/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cut_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:51:49 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/10 23:21:45 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_command_chunk(char **command, char *line, int *i)
{
	int	len;

	len = str_get_index(line, '|');
	if (!nmalloc((void **)command, len + 1))
		return (0);
	*i += len;
	while (len--)
		(*command)[len] = line[len];
	return (1);
}

int	split_pipes(t_command *cmd_lst, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!cmd_lst)
			return (0);
		if (!get_command_chunk(&(cmd_lst->command), line + i, &i))
			return (0);
		if (line[i + 1])
		{
			cmd_lst->next = create_new_chunk();
			cmd_lst = cmd_lst->next;
		}
		i++;
	}
	return (1);
}

/*int	split_args(t_command *cmd_lst)
{
	return (1);
}*/

/*int	parse_redirs(t_command *cmd_lst)
{
	return (1);
}*/
