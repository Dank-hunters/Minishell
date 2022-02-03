/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:02:27 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/03 17:50:22 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char		*new_chunk(char *str)
{
	
}

t_command	*parsing(char *line)
{
	int			i;
	int			len;
	t_command	*command;

	i = 0;
	command = (t_command *)malloc(sizeof(t_command));
	if (line[i])
	{
		if (line[i] == '\'')
			command->chunk = get_quote_content(line + i);
		else if (line[i] == '"')
			command->chunk = get_dquote_content(line + i);
		else if (line[i] == '|')
			command->chunk = new_chunk("|");
		else if (line[i] == '<')
			command->chunk = new_chunk("<");
		else if (line[i] == '>')
			command->chunk = new_chunk(">");
		else if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
			command->chunk = new_chunk("<<");
		else if (line[i] == '>' && line[i + 1] && line[i + 1] == '>')
			command->chunk = new_chunk(">>");

	}
	return (command);
}



//chart 
//
