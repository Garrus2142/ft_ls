/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:02:01 by thugo             #+#    #+#             */
/*   Updated: 2016/11/07 12:08:33 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int				i;
	unsigned char	c_char;
	unsigned char	*b_char;

	i = 0;
	c_char = (unsigned char)c;
	b_char = (unsigned char *)b;
	while (i < (int)len)
	{
		b_char[i] = c_char;
		i++;
	}
	return (b);
}
