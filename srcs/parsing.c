/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:02:27 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/23 16:57:13 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (!line[i])
				return (0);
		}
		else if (line[i] && line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (!line[i])
				return (0);
		}
		i++;
	}
	return (1);
}

t_cmd_lst	*parse_command(t_lst *env, char *line)
{
	t_command	*cmd_lst;
	t_cmd_lst	*cmd_ctrl;
	(void)env;
	cmd_lst = create_new_chunk();
	cmd_ctrl = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	if (!cmd_lst || !cmd_ctrl)
		return (error(MEMALFAILED));
	cmd_ctrl->first = cmd_lst;
	if (!check_quotes(line))
		return (error(UNCLOSEDQUOTES));
	if (!split_pipes(cmd_lst, line) /*|| !parse_redirs()*/ || \
			!split_args(cmd_ctrl->first, 0, 0))
		return (error(MEMALFAILED));
    while (cmd_lst)
    {
        cmd_lst->args[0] = cmd_lst->command;
        cmd_lst = cmd_lst->next;
    }
	if (!expand_dollars(env, cmd_ctrl->first))
		return (error(MEMALFAILED));

	/////////////////////// AFFICHAGE /////////////////////
	cmd_lst = cmd_ctrl->first;
    int i;
	while (cmd_lst)
	{
		i = 1;
		dprintf(1, "cmd : |%s|\n", cmd_lst->command);
		while(cmd_lst->args[i]) 
			dprintf(1, "args :|%s|\n", cmd_lst->args[i++]);
		cmd_lst = cmd_lst->next;
	}

	return (cmd_ctrl);
}
