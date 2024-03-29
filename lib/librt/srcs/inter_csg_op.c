/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_csg_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 00:38:47 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:56:06 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "csg.h"
#include "libft.h"
#include <math.h>

static inline t_inter
	not_op_plane(t_inter core, t_inter sub)
{
	t_inter no_inter;

	inter_set(&no_inter, sub.ray);
	if (ft_btwf(core.dist, sub.hit_pts.x, sub.hit_pts.y))
		return (no_inter);
	return (core);
}

static inline t_inter
	not_op(t_inter core, t_inter sub, t_inter no_inter)
{
	if ((core.dist < sub.hit_pts.x && core.dist < sub.hit_pts.y)
		|| core.dist == INFINITY || sub.hit_pts.x == INFINITY)
		return (core);
	if (core.obj && core.obj->type == 0)
		return (not_op_plane(core, sub));
	if (sub.dist < core.dist)
	{
		if (core.hit_pts.y < 0 && core.hit_pts.x > 0)
			return (sub);
		if (ft_btwf(sub.hit_pts.y, core.hit_pts.x, core.hit_pts.y))
		{
			sub.dist = sub.hit_pts.y;
			return (sub);
		}
	}
	if (core.dist > sub.hit_pts.y && core.dist > sub.hit_pts.x)
		return (core);
	if ((sub.obj->type == 1 && core.dist < sub.dist && sub.hit_pts.y < 0
		&& ft_btwf(sub.hit_pts.x, core.hit_pts.x, core.hit_pts.y))
		|| (sub.obj->type == 3 && sub.hit_pts.y < 0 && core.hit_pts.y > 0
		&& ft_btwf(sub.hit_pts.x, core.hit_pts.x, core.hit_pts.y)))
		return (sub);
	return (no_inter);
}

static inline t_inter
	union_op(t_inter left, t_inter right)
{
	if (left.dist <= right.dist)
		return (left);
	return (right);
}

static inline t_inter
	inter_op(t_inter left, t_inter right)
{
	t_inter no_inter;

	inter_set(&no_inter, left.ray);
	if (left.dist == INFINITY || right.dist == INFINITY)
		return (no_inter);
	if (right.hit_pts.y > 0 && ft_btwf(right.dist, left.dist, left.hit_pts.y)
		&& left.obj && left.obj->type != 0)
		return (right);
	if (ft_btwf(left.dist, right.hit_pts.x, right.hit_pts.y))
		return (left);
	if (left.obj && left.obj->type == 0)
		return (no_inter);
	if (ft_btwf(right.dist, left.hit_pts.x, left.hit_pts.y))
		return (right);
	return (no_inter);
}

t_inter
	inter_from_csg_op(int type, t_inter left, t_inter right, t_ray incoming)
{
	t_inter no_inter;

	inter_set(&no_inter, incoming);
	if (right.obj != NULL && right.obj->type == 2
		&& is_inside_cone(&right))
	{
		if (type == INTER)
			return (not_op(left, right, no_inter));
		if (type == NOT)
			return (inter_op(left, right));
	}
	if (left.obj != NULL && left.obj->type == 2
		&& is_inside_cone(&left) && type == INTER)
		return (not_op(right, left, no_inter));
	if (right.obj != NULL && right.obj->type == 0 && type == NOT)
		return (not_plane(left, right));
	if (type == INTER)
		return (inter_op(left, right));
	if (type == NOT)
		return (not_op(left, right, no_inter));
	if (type == UNION)
		return (union_op(left, right));
	ft_error(__func__, __LINE__);
	return (no_inter);
}
