/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:09:20 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:48:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
# define GL_SILENCE_DEPRECATION

# include "t_data.h"
# include "csg.h"
# include "cimgui.h"

# define FLAGS1	ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar
# define FLAGS2	ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar
# define FLAGS3	ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse
# define FLAGS4	ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove
# define RENDER_FLAGS FLAGS1 | FLAGS2 | FLAGS3 | FLAGS4

/*
** Hooks :
*/

void	toggle_fullscreen(t_sdl *sdl, t_gui *gui);
void	toggle_layout(t_sdl *sdl, t_gui *gui);
void	resize_app(int width, int height, t_data *app);
void	err_win(t_gui *gui);
void	export_win(t_gui *gui);
void	load_win(t_gui *gui);
void	stats_win(t_gui *gui);
void	selector(t_gui *gui);
void	add_obj_win(t_gui *gui);
void	del_obj_win(t_gui *gui);
void	del_light_win(t_gui *gui);
void	render_win(t_gui *gui);
void	keymap_win(t_gui *gui);
void	about_win(t_gui *gui);
void	ui_object(t_data *app, t_obj *obj);
void	ui_scene_editor(t_gui *gui);
void	ui_mainmenu(t_gui *gui);
void	add_cluster_win(t_gui *gui);
void	obj_ui(t_gui *gui);

void	ui_render_settings(t_data *app);
int		export_scene(t_data *app, char *filename);
void	reload_scene(t_data *app, char *filename);
void	camera_tab(t_data *app);

void	anim_add(t_data *app, t_obj *obj);
void	anim_delete(t_data *app);
void	animate(t_data *app);
void	anim_reset(t_data *app);
void	anim_add_light(t_data *app, t_light *light);

void	export_material(int fd, t_material *mat);
bool	load_selected_tex(const char *label, char *name, t_list *current,
	t_texture **selected);
void	anim_ui(t_gui *gui);
void	anim_add_another(t_anim *anim);
void	anim_selector(t_gui *gui, ImVec2 size);
void	anim_del_one(t_data *app, t_anim *anim, t_anim *to_del);

/*
** Prototypes :
*/

void	material_list(t_list *lst_mat, t_material *mat);
void	node_type_list(t_csg_op *csg_op);
void	new_obj_list(int *type);
void	list_scenes(t_gui *gui);
void	new_light(t_data *app);
void	new_obj(t_data *app, int type);
void	delete_obj(t_data *app);
void	delete_light(t_data *app);
bool	check_file(char *filename);
void	edit_color_mat(t_color *target, char *label, t_material *mat);
void	new_cluster(t_data *app, int type);
void	ui_apply_rotation(t_vec3 *x, t_vec3 *y, t_vec3 *z);

/*
** UI SHAPES
*/

void	ui_csg(void *app_v, void *shape);
void	ui_sphere(void *ap, void *shape);
void	ui_plane(void *app_v, void *shape);
void	ui_cone(void *app_v, void *shape);
void	ui_cube(void *app_v, void *shape);
void	ui_tore(void *app_v, void *shape);
void	ui_cylinder(void *app_v, void *shape);
void	ui_light(t_data *app, t_light *light);
void	ui_cluster(t_cluster *cluster);

/*
** Hooks :
*/

void	render_gui(void *arg);
void	update(void *data);
void	key_event(int *quit, SDL_Keycode key, void *arg, bool state);
void	mouse_motion(SDL_Event *event, void *arg);
void	click_event(SDL_Event *event, void *arg);

#endif
