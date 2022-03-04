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

	new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return (0);
	new->key = key(path);
	new->value = value(path);
	new->set = 1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_command	*create_new_chunk(void)
{
	t_command *chunk;

	if (!nmalloc((void **)&chunk, sizeof(t_command)))
		return (0);
	chunk->command = 0;
	chunk->args = 0;
	chunk->redir_in_type = 0;
	chunk->redir_in_path = 0;
	chunk->redir_out_type = 0;
	chunk->redir_out_path = 0;
	chunk->fd[0] = 0;
	chunk->fd[1] = 0;
	chunk->next = 0;
	chunk->prev = 0;
	return (chunk);
}

void	free_env_lst(t_env *env)
{
		t_env *tmp;

		while (env)
		{
				tmp = env->next;
				if (env->key)
						free(env->key);
				if (env->value)
						free(env->value);
				free(env);
				env = tmp;
		}
}

void	free_cmd_lst(t_command *cmd)
{
		int i;
		t_command *tmp;

		while (cmd)
		{
				i = 0;
				while (cmd->args && cmd->args[i])
				{
						free(cmd->args[i]);
						i++;
				}
				free(cmd->args);
				free(cmd->command);
				free(cmd->redir_in_path);
				free(cmd->redir_out_path);
				tmp = cmd->next;
				free(cmd);
				cmd = tmp;
		}
}
