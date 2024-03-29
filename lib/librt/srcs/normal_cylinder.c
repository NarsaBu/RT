/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:45:24 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void	normal_cylinder(t_inter *inter)
{
	t_cylinder	*cylinder;
	t_pt3		pc;
	float		var;
	t_vec3		normal;

	cylinder = inter->obj->shape;
	vec3_sub(&normal, &inter->point, &cylinder->origin);
	var = vec3_dot(&cylinder->n, &normal);
	pc.x = cylinder->origin.x + var * cylinder->n.x;
	pc.y = cylinder->origin.y + var * cylinder->n.y;
	pc.z = cylinder->origin.z + var * cylinder->n.z;
	vec3_sub(&normal, &inter->point, &pc);
	vec3_normalize(&normal);
	if (vec3_dot(&normal, &inter->ray.dir) > 0)
		vec3_scalar(&normal, -1);
	inter->n = normal;
}
