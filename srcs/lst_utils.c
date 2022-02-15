/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:38:29 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/14 16:07:11 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*create_env_elem(char *path)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env)); /// securitteeeee
	new->key = key(path);
	new->value = value(path);
	new->set = 1;
	new->next = NULL;
	return (new);
}

t_command	*create_new_chunk(void)
{
	t_command *chunk;

	if (!nmalloc((void **)&chunk, sizeof(t_command)))
		return (0);
	chunk->command = 0;
	chunk->args = 0;
	chunk->piped = 0;
	chunk->redir_in = 0;
	chunk->redir_in_path = 0;
	chunk->redir_out = 0;
	chunk->redir_out_path = 0;
	chunk->next = 0;
	return (chunk);
}
