/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:02:50 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/14 21:02:52 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MEMALFAILED "Error : memory allocation failed\n"
# define UNCLOSEDQUOTES "Error : the command you typed contains unclosed quotes\n"

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

//env
int		get_env_size(char **envr);
t_lst	*init_env_ctrl(char **envr);
void	init_env_lst(t_lst *lst, char **envr, int size);
t_env	*create_env_elem(char *path);
void	aff_key(t_lst *data, char *str); // affiche la cle demande,
char *get_value(t_lst *data, char *key);
t_env	*get_key(t_lst *data, char *key);

//main	
int	main(int ac, char **av, char **const	envr);

//utils
void		ft_putstr(char *str);
int			ft_strlen(char *str);
int			ft_strcmp(char *s1, char *s2);
int			str_get_index(char *str, char c);
char		*ft_strdup(char *s);
char		*trim_spaces(char *str);

// norm_alloc_utils
void    	*nmalloc(void **var, int size);
void	*insalloc(void **ptr, void *mem_to_add, int starti, int endi);

//initlst
char *key(char *str);
char	*value(char *str);
void	init_env_lst(t_lst *lst, char **envr, int size);

//builtinS
//

void	env(t_lst *data, int ntm);
void	unset(t_lst *data, char *key);
void	expor(t_lst *data, char *path);
void	cd(t_lst *data, char *path);

//parsing
t_command		*create_new_chunk(void);
t_cmd_lst		*parse_command(t_lst *env, char *line);
int				split_pipes(t_command *cmd_lst, char *line);
int	expand_dollars(t_lst *env, t_command *cmd_lst);

//error
void	*error(char *err_msg);

#endif
