/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_csg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 02:02:38 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:56:06 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "csg.h"
#include "export.h"

static inline void
	export_obj_from_btree(int fd, t_obj *node_content)
{
	dprintf(fd, "\t\tobject(%s)\n\t\t{\n", get_obj_str(node_content->type));
	node_content->export(fd, node_content->shape);
	export_material(fd, &node_content->material);
	dprintf(fd, "\t\t}\n");
}

static inline void
	export_csg_op(int fd, t_csg_op *node_content)
{
	int type;

	type = node_content->type;
	if (type == INTER)
		dprintf(fd, "\t\t%s\n", INTER_STR);
	if (type == NOT)
		dprintf(fd, "\t\t%s\n", NOT_STR);
	if (type == UNION)
		dprintf(fd, "\t\t%s\n", UNION_STR);
}

static inline void
	export_btree(int fd, void *content, size_t content_size)
{
	if (content_size == sizeof(t_obj))
		export_obj_from_btree(fd, (t_obj*)content);
	else
		export_csg_op(fd, (t_csg_op*)content);
}

void
	csg_export(int fd, void *shape)
{
	t_csg *pcsg;

	pcsg = shape;
	export_tvec3(fd, "\torigin", pcsg->origin);
	export_tvec3(fd, "\tnormal", pcsg->n);
	ft_b3apply_prefix_wtarg(fd, pcsg->root, &export_btree);
}
