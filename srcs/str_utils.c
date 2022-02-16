/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:40:26 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/16 17:08:59 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strlen(char *str)
{
	char	*sstr;

	if (!str)
		return (0);
	sstr = str;
	while (*str)
		str++;
	return (str - sstr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] || str2[i]) && (str1[i] == str2[i]))
		i++;
	return (str1[i] - str2[i]);
}

int	str_get_index(char *str, char c)
{
	char *sstr;

	sstr = str;
	while (*str && *str != c)
		str++;
	return (str - sstr);
}

int	excess_spaces(char *str)
{
	int	i;
	int	len_to_trim;

	len_to_trim = 0;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	len_to_trim = i;
	while (str[i] && str[i] != ' ')
		i++;
	str += i;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	len_to_trim += i;
	return (len_to_trim);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest || !s)
		return (NULL);
	i = -1;
	while (s[++i])
		dest[i] = s[i];
	dest[i] = 0;
	return (dest);
}

char	*trim_spaces(char *str)
{
	int		i;
	int		j;
	char	*nstr;

	if (!(nmalloc((void **)&nstr, ft_strlen(str) - excess_spaces(str) + 1)))
		return (0);
	i = 0;
	j = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
	{
		nstr[j] = str[i];
		i++;
		j++;
	}
	return (nstr);
}
