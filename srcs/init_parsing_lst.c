/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:45:14 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/09 19:50:28 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*create_chunk(void)
{
	t_command *chunk;

	chunk = (t_command *)malloc(sizeof(t_command));
	chunk->args = 0;
	chunk->piped = 0;
	chunk->redir_in = 0;
	chunk->redir_in_path = 0;
	chunk->redir_out = 0;
	chunk->redir_out_path = 0;
	chunk->next = 0;
	return (chunk);
}
