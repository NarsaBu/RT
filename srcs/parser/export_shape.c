/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:21:36 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:56:06 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "export.h"
#include <stdio.h>

void
	plane_export(int fd, void *shape)
{
	t_plane		*plane;

	plane = shape;
	export_tvec3(fd, "\torigin", plane->origin);
	export_tvec3(fd, "\tnormal", plane->n);
	export_tvec3(fd, "\tx", plane->x);
	export_tvec3(fd, "\ty", plane->y);
	dprintf(fd, "\t\tlimit(%.3f %.3f)\n", plane->size.x, plane->size.y);
	dprintf(fd, "\t\ttype(%d)\n", plane->type);
	if (plane->type == 2)
	{
		dprintf(fd, "\t\tp1(%.3f %.3f)\n", plane->p1.x, plane->p1.y);
		dprintf(fd, "\t\tp2(%.3f %.3f)\n", plane->p2.x, plane->p2.y);
	}
}

void
	sphere_export(int fd, void *shape)
{
	t_sphere	*sphere;

	sphere = shape;
	export_tvec3(fd, "\torigin", sphere->origin);
	export_tvec3(fd, "\tx", sphere->x);
	export_tvec3(fd, "\ty", sphere->y);
	export_tvec3(fd, "\tz", sphere->z);
	dprintf(fd, "\t\tradius(%.3f)\n", sphere->radius);
}

void
	cone_export(int fd, void *shape)
{
	t_cone	*cone;

	cone = shape;
	export_tvec3(fd, "\torigin", cone->origin);
	export_tvec3(fd, "\tnormal", cone->n);
	export_tvec3(fd, "\tx", cone->x);
	export_tvec3(fd, "\tz", cone->z);
	dprintf(fd, "\t\ttheta(%.3f)\n", cone->theta);
	dprintf(fd, "\t\tsize(%.3f)\n", cone->size);
}

void
	cylinder_export(int fd, void *shape)
{
	t_cylinder	*cylinder;

	cylinder = shape;
	export_tvec3(fd, "\torigin", cylinder->origin);
	export_tvec3(fd, "\tnormal", cylinder->n);
	export_tvec3(fd, "\tx", cylinder->x);
	export_tvec3(fd, "\tz", cylinder->z);
	dprintf(fd, "\t\tradius(%.3f)\n", cylinder->radius);
	dprintf(fd, "\t\tsize(%.3f)\n", cylinder->size);
}

void
	cube_export(int fd, void *shape)
{
	t_cube	*cube;

	cube = shape;
	export_tvec3(fd, "\torigin", cube->origin);
	export_tvec3(fd, "\tnormal", cube->n);
	export_tvec3(fd, "\tx", cube->x);
	export_tvec3(fd, "\tz", cube->z);
	dprintf(fd, "\t\tsize(%.3f)\n", cube->size);
}
