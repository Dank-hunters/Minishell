/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:49:34 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/24 17:49:35 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:20:58 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/24 17:45:23 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skipquotes(char *str, int *i, char quote)
{
	str[(*i)++] = '\n';
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		str[(*i)++] = '\n';
}

int	buildkey(t_lst *env, char *str, char **key, int *i)
{
	int	j;
	int iq;
	int len;

	j = 0;
	iq = 0;
	while (str[j])
		if (str[j++] == '\n')
			iq = 1;
	len = ++(*i) - *i;
	while (str[*i + len] && str[*i + len] != ' ' && str[*i + len] != '\n' \
			&& str[*i + len] != '\'' && str[*i + len] != '$' \
			&& str[*i + len] != '"')
		len++;
	if (!iq && len == 0 && (str[*i + len] == '\'' || str[*i + len] == '"'))
		str[(*i) + len - 1] = '\n';
	if (!nmalloc((void **)key, len + 1))
		return (0);
	j = len;
	//dprintf(1, "|I AVANT BOUCLE:%i|\n", *i);
	*i += len;
	while (j--)
		(*key)[j] = str[--(*i)];
	*key = ft_strdup(get_value(env, *key));
	//	dprintf(1, "i|I APRES BOUCLE:%i|\n", *i);
	*i += ft_strlen(*key) - 1;
	return (len); //fffrrrrrrrrrrrrrreeeeeeeeeeeeeeeeeee
}

int	dollar_replace(t_lst *env, char **str, char *nstr, int *i)
{
	int		j;
	int		keylen;
	char	*key;
	int     iq;

	j = 0;
	iq = 0;
	while (nstr[*i] && !((!iq && nstr[*i] == ' ') || \
		(iq && nstr[*i] == '\n') || (!iq && nstr[*i] == '\'')))
	{
		j = *i;
		if (nstr[j] == '"' && ((*i)++ + 1) && (++iq || 1))
			skipquotes(nstr, &j, '"');
		if (nstr[*i] == '$')
		{	
			keylen = buildkey(env, nstr, &key, i);
			if (!insalloc((void **)&nstr, key, *i - ft_strlen(key), \
										*i - ft_strlen(key) + keylen + 1))
				return (0);
			*str = nstr;
		}
		if (nstr[*i] && (nstr[*i] != '$' || !keylen) && !(!iq && nstr[*i] == '\''))
			(*i)++;
	}
	return (1);
}

int	dollar_ptlc(t_lst *env, char **str, int i)
{
	char	*sstr;

	sstr = *str;
	while (sstr[i])
	{
		if (sstr[i] == '\'')
			skipquotes(sstr, &i, '\'');
		if (sstr[i] && sstr[i] != '\'')
		{
			if (!dollar_replace(env, str, sstr, &i))
				return (0);
			sstr = *str;
		}
		i += (sstr[i] != 0 && sstr[i] != '\'');
	}
	i = 0;
	while (sstr[i])
	{
		if (sstr[i] == '\n' && !dealloc((void **)str, i, i + 1) && (i-- + 2))
			return (0);
		sstr = *str;
		i += (sstr[i] != 0 && sstr[i] != '\n');
	}
	return (1);
}

int	expand_dollars(t_lst *env, t_command *cmd_lst)
{
	int i;

	(void)i;
	while (cmd_lst)
	{
		if (!dollar_ptlc(env, &(cmd_lst->command), 0))
			return (0);
		i = 1;
		while (cmd_lst->args[i])
		{
			if (!dollar_ptlc(env, &(cmd_lst->args[i]), 0))
				return (0);
			i++;
		}
		cmd_lst = cmd_lst->next;
	}
	return (1);
}

