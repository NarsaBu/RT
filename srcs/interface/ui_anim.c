/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:26:12 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:48:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "animate.h"
#include "libft.h"

void
	anim_list(t_anim *anim, char *str)
{
	const char			**item;
	static const char	*item_current;
	int					i;
	bool				is_selected;

	item = (const char*[]){"None", "Translation", "Orbit around Object",
		"Orbit aound Pos", "Rotation"};
	item_current = item[anim->type];
	if (igBeginCombo(str, item_current, 0))
	{
		i = -1;
		while (++i < 5)
		{
			is_selected = (item_current == item[i]);
			if (igSelectable(item[i], is_selected, 0, (ImVec2){0, 0}))
			{
				item_current = item[i];
				anim_set(anim, i);
			}
			if (is_selected)
				igSetItemDefaultFocus();
		}
		igEndCombo();
	}
	ft_strdel(&str);
}

static inline void
	anim_buttons(t_gui *gui, ImVec2 size)
{
	igSpacing();
	igSameLine(size.x / 12, 0);
	if (igButton("Play", (ImVec2){size.x / 6 - 1, 0}))
		gui->animate = 1;
	igSameLine(0, 2);
	if (igButton("Pause", (ImVec2){size.x / 6 - 1, 0}))
		gui->animate = 0;
	igSameLine(0, size.x / 6);
	if (igButton("Delete Animation", (ImVec2){size.x / 3, 0}))
		anim_delete(gui->app);
	igSpacing();
	igSameLine(size.x / 12, 0);
	if (igButton("Animate One Frame", (ImVec2){size.x / 3, 0}))
		animate(gui->app);
	igSameLine(0, size.x / 6);
	if (igButton("Reset Objects Position", (ImVec2){size.x / 3, 0}))
		anim_reset(gui->app);
	igSeparator();
}

static inline void
	anim_frames(t_gui *gui)
{
	igText("Animated frames rendered : %d", gui->animated_frames);
	igDragInt("Frame Limit", &gui->frame_limit, 1, 0, 100000, "%d");
	igCheckbox("Record Frames", &gui->record);
	igSeparator();
}

static inline int
	anim_detail(t_gui *gui, t_anim *anim, int i, ImVec2 size)
{
	char	*str_list __attribute__((cleanup(ft_strdel)));

	if (!(str_list = ft_strjoini("Movement ", i)))
		ft_error(__func__, __LINE__);
	anim_list(anim, str_list);
	igSameLine(0, 10);
	if (!(str_list = ft_strjoini("Delete ", i)))
		ft_error(__func__, __LINE__);
	if (igButton(str_list, (ImVec2){0, 0}))
	{
		anim_del_one(gui->app, gui->anim_set, anim);
		return (EXIT_FAILURE);
	}
	if (anim->ui_anim)
		anim->ui_anim(anim, i);
	igSeparator();
	if (!anim->next)
		if (igButton("Add Animation to Object", (ImVec2){size.x / 3, 0}))
			anim_add_another(anim);
	return (EXIT_SUCCESS);
}

void
	anim_ui(t_gui *gui)
{
	t_anim	*anim;
	int		i;
	ImVec2	size;

	size = igGetWindowSize();
	anim_selector(gui, size);
	anim_buttons(gui, size);
	anim_frames(gui);
	anim = gui->anim_set;
	i = 0;
	while (anim)
	{
		if (anim_detail(gui, anim, i, size))
			break ;
		anim = anim->next;
		i++;
	}
	igEndTabItem();
}
