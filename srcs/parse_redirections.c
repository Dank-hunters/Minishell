/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:49:30 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/22 18:49:39 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_path_len(char *line)
{
    int i;

    i = 0;
    while (line[i] != ' ')
    {
       if (line[i] == '\'' && ++i)
            while (line[i] != '\'')
               i++;
       if (line[i] == '"' && ++i)
           while (line[i] != '"')
               i++;
       i++;
    }
    return (i);
}

int get_redir_path(t_command *cmd_lst, char *line, int *i, int type)
{
    int pathlen;

    (*i)++;
    while (*line == ' ')
        line++;
    pathlen = get_path_len(line + *i);
    if (type == 1 && free(cmd_lst->redir_in_path))
    {
        if (!nmalloc((void **)&(cmd_lst->redir_in_path), pathlen + 1))
            return (0);
        ft_strncpy(cmd_lst->redir_in_path, line, pathlen);
    }
    else if (free(cmd_lst->redir_out_path))
    {
        if (!nmalloc((void **)&(cmd_lst->redir_out_path), pathlen + 1))
            return (0);
        ft_strncpy(cmd_lst->redir_out_path, line, pathlen);
    }
}

int	parse_guillemets_in(t_command *cmd_lst, char *line, int i, int fd)
{
    int starti;
    int endi;

    while (line[i])
    {
        if (line[i] == '<' && ++i)
        {
            starti = i;
            cmd_lst->redir_in_type = 1 + (line[i] == '<');
            cmd_lst->redir_in_path = get_redir_path(line, &i, 1);
            endi = i;
            if (!cmd_lst->redir_in_path || !dealloc(cmd_lst->command, starti, endi))
                return (0);
            if (fd)
                close(fd);
            if (cmd_lst->redir_in_type == 1)
                fd = open(cmd_lst->redir | O_RDWR | O_CREAT);
            else
                fd = open(cmd_lst->redir | O_RDWR | O_CREAT);
            if (fd = -1)
                return (0)
        }
    }
    return (fd);
}

int	parse_guillemets_out(t_command *cmd_lst, char *line, int i, int fd)
{
    int     starti;
    int     endi;

    while (line[i])
    {
        if (line[i] == '>' && ++i)
        {
            starti = i;
            cmd_lst->redir_out_type = 1 + (line[i] == '>');
            cmd_lst->redir_out_path = get_redir_path(line, &i, 2);
            endi = i;
            if (!cmd_lst->redir_out_path || \
                !dealloc(cmd_lst->command, starti, endi))
                return (0);
            if (fd)
                close(fd);
            if (cmd_lst->redir_in_type == 1)
                fd = open(cmd_lst->redir | O_RDWR | O_CREAT);
            else
                fd = open(cmd_lst->redir | O_RDWR | O_CREAT | O_APPEND);
            if (fd = -1)
                return (0)
        }
    }
    return (fd);
}

int parse_redirs(t_command *cmd_lst, char *line)
{ 
    if (!parse_guillemets(cmd_ctrl->first, line, '<', 0, 0) || \
        !parse_guillemets(cmd_ctrl->first, line, '>', 0, 0))
        return (0);
    return (1);
}
