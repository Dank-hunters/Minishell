/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@istudent.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:18:14 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/15 19:23:01 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*nmalloc(void **var, int size)
{
	*var = malloc(sizeof(char) * size);
	if (!(*var))
		return (NULL);
	while (size--)
		((char *)(*var))[size] = 0;
	return (*var);
}

void	*nealloc(void **ptr, int size_supp)
{
	int		slen;
	char	*tmptr;

	slen = ft_strlen(*(char **)ptr);
	tmptr = (char *)malloc(sizeof(char) * (slen + size_supp));
	if (!tmptr)
		return (0);
	if (*(char **)ptr && *(*(char **)ptr))
	{
		while (*(*(char **)ptr))
			*(tmptr++) = *((*(char **)ptr)++);
		*tmptr = 0;
	}
	free(*(char **)ptr - slen);
	*ptr = tmptr - slen;
	return (*ptr);
}

void	*insalloc(void **ptr, void *mem_to_add, int starti, int endi)
{
	int	i;
	int	slen;
	int chunklen;
	char	*tmptr;

	tmptr = 0;
	slen = ft_strlen(*(char **)ptr);
	chunklen = ft_strlen((char *)mem_to_add);
	if (!mem_to_add || !nmalloc((void **)&tmptr, \
									slen + chunklen - (endi - starti) + 2))
		return (0);
	i = -1;
	if (*(char **)ptr)
	{
		while ((++i + 1) && (*(char **)ptr)[i] && i < starti)
			tmptr[i] = (*(char **)ptr)[i];
		while (*(char *)mem_to_add)
			tmptr[i++] = *(char *)mem_to_add++;
		while ((*(char **)ptr)[endi])
			tmptr[i++] = (*(char **)ptr)[endi++];
	}
	free(mem_to_add - chunklen);
	free(*ptr);
	*ptr = tmptr;
	return (tmptr);
}

void	*dealloc(void **ptr, int starti, int endi)
{
	int	i;
	int	j;
	int	slen;
	char	*tmptr;

	slen = ft_strlen(*(char **)ptr);
	if (!nmalloc((void **)&tmptr, slen - (endi - starti) + 1))
		return (0);
	i = 0;
	while ((*(char **)ptr)[i] && i < starti)
		((char *)tmptr)[i] = (*(char **)ptr)[i];
	j = i;
	while (j < endi)
		j++;
	while ((*(char **)ptr)[j])
	{
		((char *)tmptr)[i] = (*(char **)ptr)[j];
		i++;
		j++;
	}
	free(*ptr);
	*ptr = tmptr;
	return (tmptr);
}
