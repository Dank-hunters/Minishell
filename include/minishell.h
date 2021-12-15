/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:02:50 by cguiot            #+#    #+#             */
/*   Updated: 2021/12/15 17:13:56 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	int				set ;
	struct s_env	*next;

}				t_env;

typedef struct s_lst
{
	t_env	*first;
	t_env	*last;
	int		size;
}				t_lst;

//initlst
t_lst	init_env_ctrl(char **envr);
void	init_env_lst(t_lst *lst, char **envr, int size);
void	*creat_elem(char *path);

//main	
int	main(int ac, char **av, char **const	envr);


//utils
void		ft_putstr(char *str);
void		ft_putstr_fd(int fd, char *str);
void	aff_key(t_lst *data, char *str); // affiche la cle demande,

#endif
