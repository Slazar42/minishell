/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:18:49 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 23:13:09 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dc;
	unsigned char	*cc;

	dc = (unsigned char *)dst;
	cc = (unsigned char *)src;
	if (!dc && !cc)
		return (0);
	while (n--)
		dc[n] = cc[n];
	return (dst);
}
