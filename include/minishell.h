/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:02:50 by cguiot            #+#    #+#             */
/*   Updated: 2022/02/16 18:30:56 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
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
	struct s_env	*prev;

}				t_env;

typedef struct s_command
{
	char				*command;
	char				**args;
	int					redir_in_type;
	char				*redir_in_path;
    int                 redir_in_fd;
	int					redir_out_type;
	char				*redir_out_path;
    int                 redir_out_fd;
	struct s_command	*next;
	struct s_command	*prev;
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
char		*ft_strjoin(char *s1, char *s2, int frees1, int frees2);
char		*ft_strdup(char *s, int frees1);
int		    trim_spaces(char **str);
char        *ft_strncpy(char *dest, char *src, int len);
char        **ft_split(char *str, char c);
int         ft_strchr(char *str, char c);
// norm_alloc_utils
void	*nmalloc(void **var, int size);
void	*insalloc(void **ptr, void *mem_to_add, int starti, int endi);
void	*dealloc(void **ptr, int starti, int endi);
void    *nmalloc_2d(char ***var, int sizey);

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
int     		parse_redirs(t_command *cmd_lst, t_lst *env);
int		split_pipes(t_command *cmd_lst, char *line);
int		split_args(t_command *cmd_lst, int i, int y);
int		expand_dollars(t_lst *env, t_command *cmd_lst);
int	dollar_ptlc(t_lst *env, char **str, int i);

//exec
int execute(t_command *cmd_lst, t_lst *env);

//void		iter_through_word(char *str, int *i);		
int	get_arg(t_command *cmd_lst, int *i, int *y);

//error
void	*error(char *err_msg);

#endif
