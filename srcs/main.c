/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:02:17 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/16 18:56:39 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_closed(char *str)
{
		int	i;

		i = 0;
		if (str == NULL)
				return (1);
		if (str[0] != 'e')
				return (1);
		if (str[1] != 'x')
				return (1);
		if (str[2] != 'i')
				return (1);
		if (str[3] != 't')
				return (1);
		if (str[4] != '\0')
				return (1);
		else
		{
				dprintf(1, "exit\n");
				return (0);	
		}
}

void	aff(t_lst *data)
{
		t_env *env;

		env = data->first;
		while (env != NULL)
		{
				dprintf(1, "%s=%s --- %i\n", env->key, env->value, env->set);
				env = env->next;
		}
}

int	prompt(char **envr)
{
		char 		*prt;
		t_lst		*data_env;
		t_cmd_lst	*cmd_ctrl;
		t_command *cmds;
		int size;

		size = get_env_size(envr);
		prt = NULL;
		data_env = init_env_ctrl(envr);
		init_env_lst(data_env, envr, size);
		while (is_closed(prt) == 1)
		{
				prt = readline("\033[36;03mMinishell-4.2 \033[33;03m$> \033[32;03m");
				add_history(prt);
				if (prt && *prt)
				{	
						cmd_ctrl = parse_command(data_env, prt);
						cmds = cmd_ctrl->first;
						while (cmds)
						{
								execute(cmds, data_env);
								cmds = cmds->next;
						}
				}
		}
		free(prt);
		return(0);
}

int main(int ac, char **av, char **const envr)
{
		(void)av;
		int i = 0;
		if (ac == 1)
				prompt(envr);
		return (i);
}
