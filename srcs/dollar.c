/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:20:58 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/14 21:12:01 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	buildkey(t_lst *env, char *str, char **key)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\n')
		i++;
	if (!nmalloc((void **)key, i + 1))
		return (0);
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\n')
	{
		(*key)[i] = str[i];
		i++;
	}
	*key = ft_strdup(get_value(env, *key));
	if (!*key)
		return (0);
	return (i);
}

void	skipquotes(char *str, int *i, char quote)
{
	str[(*i)++] = '\n';
	while (str[*i] && str[*i] != quote)
		(*i)++;
	str[(*i)++] = '\n';
}

int	dollar_replace(t_lst *env, char **str, char *nstr, int *i)
{
	int		j;
	int		keylen;
	char	*key;

	j = *i;
	while (nstr[j] && nstr[j] != ' ' && nstr[j] != '\n')
	{
		if (nstr[*i] == '"')
			skipquotes(nstr, i, '"');
		if (nstr[j] == '$')
		{
			keylen = buildkey(env, nstr, &key);
		   	if (!keylen || !insalloc((void **)&nstr, key, j, j + keylen))
				return (0);
			while (nstr[j] && nstr[j] != ' ' && nstr[j] != '\n')
				j++;
			*i = j;
		}
		j++;
	}
	*str = nstr;
	return (1);
}

int	dollar_ptlc(t_lst *env, char **str)
{
	int	i;
	char	*sstr;

	sstr = *str;
	i = 0;
	while (sstr[i])
	{
		if (sstr[i] == '\'')
			skipquotes(sstr, &i, '\'');
		if (sstr[i] && sstr[i] != '\'')
			if (!dollar_replace(env, str, sstr, &i))
				return (0);
		i++;
	}
	return (1);
}

int	expand_dollars(t_lst *env, t_command *cmd_lst)
{
	int i;

	(void)i;
	while (cmd_lst)
	{
		if (!dollar_ptlc(env, &(cmd_lst->command)))
			return (0);
		/*i = 1;
		while (cmd_lst->args[i])
		{
			if (!dollar_ptlc(&(cmd_lst->args[i])))
				return (0);
			i++;
		}*/
		cmd_lst = cmd_lst->next;
	}
	return (1);
}

