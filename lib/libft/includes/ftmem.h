/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmem.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:10:31 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMEM_H
# define FTMEM_H

# include <stddef.h>

typedef unsigned char	t_byte;

void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *str, size_t n);
void					*ft_memcpy(void *dst, void const *src, size_t n);
void					*ft_memccpy(void *dst, void const *sr, int c, size_t n);
void					*ft_memmove(void *dst, void const *src, size_t n);
void					*ft_memchr(void const *str, int c, size_t n);
int						ft_memcmp(void const *s1, void const *s2, size_t n);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
void					*ft_memrcpy(void *dst, void const *src, size_t n);
void					*ft_safe_alloc(size_t size);
void					*ft_print_memory(void *addr, size_t size);
void					*ft_memdup(void *src, size_t size);

#endif
