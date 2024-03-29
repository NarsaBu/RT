/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:35:33 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "libft.h"
#include "ftio.h"

static inline void
	putcolor(t_sdl *sdl, int color, int x, int y)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color;
	sdl->img.pixels[y * sdl->img.width + x] = color;
}

void
	render_sdl(t_sdl *sdl, int (*do_pxl) (int, int, void*), void *data)
{
	long	elapsed_time;
	t_pxl	idx;

	if (sdl->needs_render == false)
		return ;
	elapsed_time = ft_curr_usec();
	idx.y = -1;
	while (++idx.y < sdl->height_vp)
	{
		idx.x = -1;
		while (++idx.x < sdl->width_vp)
		{
			putcolor(sdl, do_pxl(idx.x, idx.y, data), idx.x, idx.y);
		}
	}
	sdl->needs_render = false;
	elapsed_time = ft_curr_usec() - elapsed_time;
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
}
