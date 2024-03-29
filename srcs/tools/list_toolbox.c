/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_toolbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 04:14:20 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:48:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"
#include "rtstruct.h"
#include "t_scene.h"

int		obj_cmp(void *res_1, void *res_2)
{
	t_obj	*obj_1;
	t_obj	*obj_2;

	obj_1 = res_1;
	obj_2 = res_2;
	return (ft_strcasecmp(obj_1->name, obj_2->name));
}

int		texture_cmp(void *res_1, void *res_2)
{
	t_texture	*tex_1;
	t_texture	*tex_2;

	tex_1 = res_1;
	tex_2 = res_2;
	return (ft_strcasecmp(tex_1->name, tex_2->name));
}

int		mat_cmp(void *res_1, void *res_2)
{
	t_material	*mat_1;
	t_material	*mat_2;

	mat_1 = res_1;
	mat_2 = res_2;
	return (ft_strcasecmp(mat_1->name, mat_2->name));
}

int		light_cmp(void *res_1, void *res_2)
{
	t_light		*light_1;
	t_light		*light_2;

	light_1 = res_1;
	light_2 = res_2;
	return (ft_strcasecmp(light_1->name, light_2->name));
}

int		scene_cmp(void *res_1, void *res_2)
{
	t_scene_name	*scene_1;
	t_scene_name	*scene_2;

	scene_1 = res_1;
	scene_2 = res_2;
	return (ft_strcasecmp(scene_1->name, scene_2->name));
}
