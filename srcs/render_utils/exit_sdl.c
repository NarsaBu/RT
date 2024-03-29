/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:52:36 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "ftmem.h"

void	exit_sdl(t_sdl *sdl)
{
	if (sdl == NULL)
		return ;
	if (sdl->win != NULL)
		SDL_DestroyWindow(sdl->win);
	if (sdl->data_thr != NULL)
		ft_memdel((void**)&sdl->data_thr);
	if (sdl->img.pixels)
		ft_memdel((void**)&sdl->img.pixels);
	ft_memdel((void**)&sdl);
	SDL_Quit();
}
