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

void	sqs(char *line, int *i, char quote)
{
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i])
		(*i)++;
}

int	sss(char *line, int *i)
{
    (*i)++;
	while (line[*i] == ' ')
		(*i)++;
	return ((line[*i] != 0));
}

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

int	check_syntax(char *s)
{
	int i;

	if (!check_quotes(s))
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			sqs(s, &i, s[i]);
		if (s[i] == '>')
			if (!sss(s, &i) || (s[i] == '>' && i && s[i - 1] == ' ') || 
			    s[i] == '<' || s[i] == '|' || !sss(s, &i) || s[i] == '>' || \
                s[i] == '|' || s[i] == '<')
				return (0);
		if (s[i] == '<')
			if (!sss(s, &i) || (s[i] == '<' && i && s[i - 1] == ' ') || 
			    s[i] == '>' || s[i] == '|' || !sss(s, &i) || s[i] == '<' || \
                s[i] == '|' || s[i] == '>')
				return (0);	
		if (s[i] == '|' && s[i + 1] == '|')
			return (0);
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
		return (0); // errmsg alloc failed
	cmd_ctrl->first = cmd_lst;
	if (!check_syntax(line))
    {
        dprintf(1, "PIUte"); 
		return (0); // errmsg syntax
    }
    if (!split_pipes(cmd_lst, line) || \
        !parse_redirs(cmd_lst, env) || \
        !split_args(cmd_ctrl->first, 0, 0))
    {
        dprintf(1, "alloc open");
        return (0); // errmsg alloc failed / open failed
    }
    if (!expand_dollars(env, cmd_ctrl->first))
    {
        dprintf(1, "alloc");
		return (0); // errmsg alloc failed
    }
    while (cmd_lst)
	{
		cmd_lst->args[0] = cmd_lst->command;
		cmd_lst = cmd_lst->next;
	}	
	/////////////////////// AFFICHAGE /////////////////////
	cmd_lst = cmd_ctrl->first;
	int i;
	while (cmd_lst)
	{
		i = 1;
		dprintf(1, "cmd : |%s|\n", cmd_lst->command);
		dprintf(1, "redir out :|%s|\n",cmd_lst->redir_out_path);
		dprintf(1, "redir in :|%s|\n",cmd_lst->redir_in_path);
//		dprintf(1, "args :|%s|\n", cmd_lst->args[i++]);
//		dprintf(1, "args :|%s|\n", cmd_lst->args[i++]);
		while(cmd_lst->args[i]) 
        {
            dprintf(1, "args :|%s|\n", cmd_lst->args[i++]);
        }
        cmd_lst = cmd_lst->next;
	}

	return (cmd_ctrl);
}
