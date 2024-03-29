/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:44:13 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:56:06 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmem.h"
#include <stdlib.h>

static inline void
	*ft_memcpy_(void *dst, void const *src, size_t n)
{
	t_byte	*pdst;
	t_byte	*psrc;

	pdst = (t_byte*)dst;
	psrc = (t_byte*)src;
	while (n--)
		*pdst++ = *psrc++;
	return (dst);
}

void
	*ft_memdup(void *src, size_t size)
{
	void	*mem;

	if (size == 0 || !(mem = malloc(size)))
		return (NULL);
	ft_memcpy_(mem, src, size);
	return (mem);
}
