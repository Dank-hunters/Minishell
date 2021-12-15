/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:02:17 by cguiot            #+#    #+#             */
/*   Updated: 2021/12/15 17:14:37 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//char *skip_sp(char str)

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
	else
		return (0);	

}

void	aff(t_lst *data)
{
	t_env *env;

	env = data->first;
	while (env != NULL)
	{
		dprintf(1, "key : %s, Code : %s, on ? : %i\n", env->key, env->value, env->set);
		env = env->next;
	}
}

int take_size(char **envr)
{
	int i;

	i = 0;
	while(envr[i])
		i++;
	return (i);
}

int	prompt(char **envr)
{
	char 	*prt;
	t_lst	data_env;
	int size;
	
	size = take_size(envr);
	prt = NULL;
	data_env = init_env_ctrl(envr);
	init_env_lst(&data_env, envr, size);
	aff(&data_env);
	while (is_closed(prt) == 1)
	{
		prt = readline("Minishell-4.2 $> ");
		add_history(prt);
		if (prt[0] == 'e' && prt[1] == 'x' && prt[2] == 'p')
			aff_key(&data_env, prt + 4);
		if (prt[0] == 's' && prt[1] == 'h' && prt[2] == 'o')
			dprintf(1, "%s\n", envr[9]);
		if (prt[0] == 'p' && prt[1] == 'w' && prt[2] == 'd')
			dprintf(1, "%s\n", envr[8] + 4);
		//prt = skip_sp(prt);
	}
	free(prt);
	return(0);
}





int main(int ac, char **av, char **const envr)
{
	(void)ac;
	(void)av;
//	int a = 0;
	int i = 0;
//	char *prompt;
	//	ft_putstr("lolilol\n");

//	if (ac == 1)
		prompt(envr); // = readline("lolilol :");
	return (i);
}
