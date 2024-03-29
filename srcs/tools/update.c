/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:16:57 by pcollio-          #+#    #+#             */
/*   Updated: 2020/05/21 10:48:05 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "librt.h"
#include "SDL_opengl.h"

void	update(void *arg)
{
	t_data *app;

	app = arg;
	update_camera(&app->cam, &app->sdl->needs_render);
}

void	update_texture(t_img img, t_gui gui)
{
	glBindTexture(GL_TEXTURE_2D, gui.texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, img.pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	render_gui(void *arg)
{
	t_data *app;

	app = arg;
	update_texture(app->sdl->img, app->gui);
	interface(app);
}
