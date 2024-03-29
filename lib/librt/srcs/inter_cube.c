/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:52:10 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 11:00:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

void
	set_min_max_corner(t_cube *cube)
{
	float size;

	size = cube->size;
	cube->min_corner.x = fminf(cube->origin.x - size, cube->origin.x + size);
	cube->min_corner.y = fminf(cube->origin.y - size, cube->origin.y + size);
	cube->min_corner.z = fminf(cube->origin.z - size, cube->origin.z + size);
	cube->max_corner.x = fmaxf(cube->origin.x - size, cube->origin.x + size);
	cube->max_corner.y = fmaxf(cube->origin.y - size, cube->origin.y + size);
	cube->max_corner.z = fmaxf(cube->origin.z - size, cube->origin.z + size);
}

static inline t_vec2
	inter_vec2(t_ray *ray, t_cube *cube)
{
	t_vec3	dirfrac;
	t_vec2	res;
	t_vec3	min_sub;
	t_vec3	max_sub;

	dirfrac.x = (ray->dir.x) ? 1.0f / ray->dir.x : 0.0f;
	dirfrac.y = (ray->dir.y) ? 1.0f / ray->dir.y : 0.0f;
	dirfrac.z = (ray->dir.z) ? 1.0f / ray->dir.z : 0.0f;
	min_sub = vec3_sub_(cube->min_corner, ray->origin);
	max_sub = vec3_sub_(cube->max_corner, ray->origin);
	min_sub = vec3_mul_(min_sub, dirfrac);
	max_sub = vec3_mul_(max_sub, dirfrac);
	res.x = fmaxf(fmaxf(fminf(min_sub.x, max_sub.x),
		fminf(min_sub.y, max_sub.y)), fminf(min_sub.z, max_sub.z));
	res.y = fminf(fminf(fmaxf(min_sub.x, max_sub.x),
		fmaxf(min_sub.y, max_sub.y)), fmaxf(min_sub.z, max_sub.z));
	if (res.y <= 0 || res.x >= res.y)
	{
		res.x = INFINITY;
		res.y = INFINITY;
		return (res);
	}
	return (res);
}

static inline float
	inter_local(t_inter *inter, t_ray *ray, t_cube *cube)
{
	t_vec2	res_local;
	t_vec2	dist;

	res_local = inter_vec2(ray, cube);
	if (res_local.x > 0 && res_local.y > 0)
	{
		dist.x = fminf(res_local.x, res_local.y);
		dist.y = fmaxf(res_local.x, res_local.y);
	}
	else if (res_local.y > 0 || res_local.x > 0)
	{
		dist.x = fmaxf(res_local.x, res_local.y);
		dist.y = fminf(res_local.x, res_local.y);
	}
	else
	{
		dist.x = INFINITY;
		dist.y = INFINITY;
	}
	if (dist.x >= inter->dist || dist.x < 0)
		return (INFINITY);
	inter->hit_pts = dist;
	return (dist.x);
}

void
	inter_cube(t_inter *inter, t_obj *node)
{
	t_cube		*cube;
	float		dist;
	t_matrix	local_matrix;
	t_ray		local_ray;
	t_vec3		ray2cube;

	cube = node->shape;
	local_matrix = mat_set_axes(cube->x, cube->n, cube->z);
	local_ray = inter->ray;
	ray2cube = vec3_sub_(local_ray.origin, cube->origin);
	apply_matrix(&ray2cube, &local_matrix);
	vec3_scalar(&local_ray.origin, -1);
	vec3_add(&local_ray.origin, &ray2cube, &cube->origin);
	apply_matrix(&local_ray.dir, &local_matrix);
	vec3_normalize(&local_ray.dir);
	dist = inter_local(inter, &local_ray, cube);
	if (dist >= inter->dist || dist < 0)
		return ;
	inter->dist = dist;
	inter->obj = node;
}

t_vec3
	get_cube_uv(t_inter *inter)
{
	t_cube	*cube;
	t_vec3	uv;
	t_vec3	local_base[2];
	t_vec3	orig_to_inter;

	cube = (t_cube *)inter->obj->shape;
	orig_to_inter = vec3_sub_(inter->point, cube->origin);
	create_orthobasis_from_y_axis(cube->n, &local_base[0], &local_base[1]);
	uv.y = vec3_dot(&orig_to_inter, &cube->n);
	uv.x = vec3_dot(&orig_to_inter, &local_base[1]);
	uv.x = remap_to_0_to_1(uv.x / cube->size);
	uv.y = remap_to_0_to_1(uv.y / cube->size);
	return (uv);
}
