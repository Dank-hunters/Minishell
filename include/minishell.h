/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:02:50 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/09 20:03:13 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MEMALFAILED "Error : Memory Allocation Failed\n"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				set ;
	struct s_env	*next;

}				t_env;

typedef struct s_command
{
	char				*command;
	char				**args;
	int					piped;
	int					redir_in;
	int					redir_in_path;
	int					redir_out;
	int					redir_out_path;
	struct s_command	*next;
}				t_command;

typedef struct s_cmd_lst
{
	t_command	*first;
	t_command	*last;
	int		size;
}			t_cmd_lst;

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
void		aff_key(t_lst *data, char *str); // affiche la cle demande,
char		*found_key(t_lst *data, char *str);
t_env	*get_key(t_lst *data, char *key);

//builtinS
//

void	env(t_lst *data, int ntm);
void	unset(t_lst *data, char *key);
void	expor(t_lst *data, char *path);
void	cd(t_lst *data, char *path);

//partsing
//

t_command	*parsing(char *line);

//init parsing lst
t_command	*create_chunk(void);

#endif
