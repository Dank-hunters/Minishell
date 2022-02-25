/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichard <lrichard@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 00:30:46 by lrichard          #+#    #+#             */
/*   Updated: 2022/02/26 00:30:48 by lrichard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncpy(char *dst, char *src, int len)
{
	char	*dest;

	dest = dst;
	if (dst && src)
	{
		while (*src && len--)
			*(dst++) = *(src++);
		if (*dst)
			*dst = 0;
	}
	return (dest);
}
