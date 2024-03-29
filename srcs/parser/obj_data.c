/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:16:47 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:56:06 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "config.h"
#include "libft.h"
#include "export.h"
#include "librt.h"
#include "interface.h"

void
	init_parse_cfg(int type, t_parse *config)
{
	const t_parse index_config[] = {
		{"plane", sizeof(t_plane), &plane_set, &plane_export},
		{"sphere", sizeof(t_sphere), &sphere_set, &sphere_export},
		{"cone", sizeof(t_cone), &cone_set, &cone_export},
		{"cylinder", sizeof(t_cylinder), &cylinder_set, &cylinder_export},
		{"cube", sizeof(t_cube), &cube_set, &cube_export},
		{"csg", sizeof(t_csg), &csg_set, &csg_export},
		{"tore", sizeof(t_tore), &tore_set, &tore_export}
	};

	if (ft_btw(type, 0, sizeof(index_config) / sizeof(t_parse)))
	{
		config = ft_memcpy(config, &index_config[type], sizeof(t_parse));
		return ;
	}
	if (DEBUG)
		ft_printf("Type is not found type : %d", type);
	config->printout = NULL;
}

char __attribute__((const))
	*get_obj_str(int type)
{
	t_parse cfg;

	init_parse_cfg(type, &cfg);
	return (cfg.printout);
}

int __attribute__((const))
	get_obj_type(char *obj_type)
{
	char	*type_tested;
	int		type;

	type = -1;
	type_tested = NULL;
	while ((type_tested = get_obj_str(++type)))
	{
		if (ft_strstr(obj_type, type_tested))
			return (type);
	}
	return (-1);
}

void
	init_obj_cfg(int type, t_objset *config)
{
	const t_objset obj_func[] = {
		{&inter_plane, &ui_plane, &normal_plane, &get_plane_uv},
		{&inter_sphere, &ui_sphere, &normal_sphere, &get_sphere_uv},
		{&inter_cone, &ui_cone, &normal_cone, &get_cone_uv},
		{&inter_cylinder, &ui_cylinder, &normal_cylinder, &get_cylinder_uv},
		{&inter_cube, &ui_cube, &normal_cube, &get_cube_uv},
		{&inter_csg, &ui_csg, NULL, NULL},
		{&inter_tore, &ui_tore, &normal_tore, &get_tore_uv}
	};

	config = ft_memcpy(config, &obj_func[type], sizeof(t_objset));
}

void
	obj_set(t_obj *obj, int type)
{
	t_objset obj_cfg;

	ft_bzero(obj, sizeof(t_obj));
	init_obj_cfg(type, &obj_cfg);
	obj->type = type;
	obj->f_inter = obj_cfg.f_inter;
	obj->f_gui = obj_cfg.f_gui;
	obj->find_normal = obj_cfg.find_normal;
	obj->get_uv = obj_cfg.get_uv;
}
