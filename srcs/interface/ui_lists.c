/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:56:49 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:48:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"
#include "parse.h"
#include "t_scene.h"

void
	list_scenes(t_gui *gui)
{
	t_list			*lst;
	t_scene_name	*scene;

	lst = gui->app->lst_scenes;
	while (lst)
	{
		scene = lst->content;
		if (igMenuItemBool(scene->name, NULL, 0, 1))
			load_scene(gui->app, scene->dir);
		lst = lst->next;
	}
	igEndMenu();
}

void
	material_list(t_list *lst_mat, t_material *mat)
{
	t_list		*current;
	t_material	*tmp;
	bool		is_selected;

	current = lst_mat;
	tmp = current->content;
	if (igBeginCombo("Material", mat->name, 0))
	{
		while (current)
		{
			is_selected = (ft_strcmp(mat->name, tmp->name) == 0);
			if (igSelectable(tmp->name, is_selected, 0, (ImVec2){0, 0}))
				*mat = *tmp;
			if (is_selected)
				igSetItemDefaultFocus();
			current = current->next;
			if (current)
				tmp = current->content;
		}
		igEndCombo();
	}
}

bool
	load_selected_tex(const char *label, char *name, t_list *current,
	t_texture **selected)
{
	t_texture	*tmp;
	bool		is_selected;

	if (!(igBeginCombo(label, name, 0)))
		return (false);
	while (current)
	{
		tmp = current->content;
		is_selected = (ft_strcmp((*selected)->name, tmp->name) == 0);
		if (igSelectable(tmp->name, is_selected, 0, (ImVec2){0, 0}))
		{
			*selected = tmp;
			if (tmp->pixels == NULL)
				load_texture(tmp);
		}
		if (is_selected)
			igSetItemDefaultFocus();
		current = current->next;
	}
	igEndCombo();
	return (true);
}

void
	new_obj_list(int *type)
{
	static const char	*item_current;
	int					i;
	bool				is_selected;
	const char			*item[] = {
		"Plane", "Sphere", "Cone", "Cylinder", "Cube", "Tore"
	};

	item_current = item[*type];
	if (igBeginCombo("Object Type", item_current, 0))
	{
		i = -1;
		while (++i < 5)
		{
			is_selected = (item_current == item[i]);
			if (igSelectable(item[i], is_selected, 0, (ImVec2){0, 0}))
			{
				item_current = item[i];
				*type = i;
			}
			if (is_selected)
				igSetItemDefaultFocus();
		}
		igEndCombo();
	}
}

void
	node_type_list(t_csg_op *csg_op)
{
	const char			**item;
	static const char	*item_current;
	int					i;
	bool				is_selected;

	item = (const char*[]){"Inter", "Not", "Union"};
	item_current = item[csg_op->type - 1];
	if (igBeginCombo("Node Type", item_current, 0))
	{
		i = -1;
		while (++i < 3)
		{
			is_selected = (item_current == item[i]);
			if (igSelectable(item[i], is_selected, 0, (ImVec2){0, 0}))
			{
				item_current = item[i];
				csg_op->type = i + 1;
			}
			if (is_selected)
				igSetItemDefaultFocus();
		}
		igEndCombo();
	}
}
