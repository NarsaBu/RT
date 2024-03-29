/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtstruct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 00:44:05 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSTRUCT_H
# define RTSTRUCT_H

# include <stdbool.h>
# include <stdint.h>
# include "ftbtree.h"
# include "color.h"

typedef struct s_obj	t_obj;
typedef struct s_inter	t_inter;

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef t_vec3	t_pt3;

typedef struct	s_matrix
{
	float		m[3][3];
}				t_matrix;

typedef struct	s_ray
{
	t_pt3		origin;
	t_vec3		dir;
}				t_ray;

typedef struct	s_plane
{
	t_pt3		origin;
	t_vec3		n;
	t_vec3		x;
	t_vec3		y;
	t_vec2		size;
	t_vec2		p1;
	t_vec2		p2;
	int			type;
}				t_plane;

typedef struct	s_sphere
{
	t_pt3		origin;
	float		radius;
	t_vec3		x;
	t_vec3		y;
	t_vec3		z;
}				t_sphere;

typedef struct	s_cone
{
	t_pt3		origin;
	t_vec3		n;
	float		theta;
	float		size;
	t_vec3		x;
	t_vec3		z;
}				t_cone;

typedef struct	s_cylinder
{
	t_pt3		origin;
	t_vec3		x;
	t_vec3		n;
	t_vec3		z;
	float		radius;
	float		size;
}				t_cylinder;

typedef struct	s_csg
{
	t_pt3		origin;
	t_vec3		x;
	t_vec3		n;
	t_vec3		z;
	t_btree		*root;
}				t_csg;

typedef struct	s_cube
{
	t_pt3		origin;
	t_vec3		x;
	t_vec3		n;
	t_vec3		z;
	t_vec3		min_corner;
	t_vec3		max_corner;
	float		size;
}				t_cube;

typedef struct	s_tore
{
	t_pt3		origin;
	t_vec3		x;
	t_vec3		n;
	t_vec3		z;
	float		radius;
	float		size;
}				t_tore;

typedef struct	s_light
{
	t_pt3		origin;
	t_color		color;
	float		intensity;
	char		*name;
	void		*anim;
}				t_light;

typedef struct	s_cam
{
	t_pt3		pos;
	t_vec3		dir;
	t_matrix	rotation;
	float		y_angle;
	float		x_angle;
	void		*anim;
	bool		move_forward;
	bool		move_backward;
	bool		strafe_left;
	bool		strafe_right;
	bool		move_upward;
	bool		move_downward;
	bool		rotate_up;
	bool		rotate_down;
	bool		rotate_left;
	bool		rotate_right;
	bool		lock;
	bool		lock_pos;
	t_pt3		pos_lock;
	bool		lock_obj;
	t_obj		*obj_lock;
	int			speed;
}				t_cam;

/*
** @brief Struct for material caracteristics
** http://www.lama.univ-savoie.fr/pagesmembres/lachaud/Cours/INFO805/Tests/html/
** Material_8h_source.html
** typedef t_color	(*f_texture)(t_texture*, float x, float y);
*/

typedef	struct s_texture	t_texture;
typedef	struct s_material	t_material;

struct			s_texture
{
	char		*name;
	char		*dir;
	t_color		(*f_texture)(t_material *, t_texture *, t_vec3);
	char		*pixels;
	int			width;
	int			height;
	char		bpp;
};

typedef struct	s_uv_mapping {
	t_vec2	offset;
	t_vec2	scale;
	bool	repeat;
}				t_uv_mapping;

/*
**	t_texture		*rough_map;
**	t_texture		*disp_map;
**	t_texture		*occlusion_map;
*/

struct			s_material
{
	char			*name;
	t_color			color_diffuse;
	t_color			color_specular;
	t_color			color_tex;
	float			spec_idx;
	float			spec_power;
	t_color			refraction_color;
	t_color			reflection_color;
	float			refraction_idx;
	t_texture		*tex;
	t_texture		*normal_map;
	t_texture		*spec_map;
	t_texture		*refract_map;
	t_uv_mapping	uv_mapping;
};

/*
** @brief Struct that hold the intersection.
** dist 		: minimal distant at the inter
** obj 			: object touch by the ray
** ray 			: Ray information
** point		: Intersection point
** n 			: Normal of the object at the inter
** reflected	: Vector director of the ray after the inter
** find_normal	: Methode to find the normal of the object hit
*/

struct			s_inter
{
	float		dist;
	t_vec2		hit_pts;
	t_obj		*obj;
	t_ray		ray;
	t_pt3		point;
	t_vec3		n;
	t_ray		deflected;
};

# define INTER		1
# define INTER_STR	"INTER"
# define NOT		2
# define NOT_STR	"NOT"
# define UNION		3
# define UNION_STR	"UNION"

/*
** @brief Struct that hold any shape and is in a t_list
** type 		: Type of the shape
** shape 		: Pointer to shape data
** material 	: Material caracteristics
** diffuse 		: Outdated
** f_inter		: final color of the pixel
*/

struct			s_obj
{
	int			type;
	void		*shape;
	char		*name;
	t_material	material;
	t_pt3		*pos;
	t_vec3		*x;
	t_vec3		*n;
	t_vec3		*z;
	void		*anim;
	void		(*f_inter) (t_inter*, t_obj*);
	void		(*find_normal) (t_inter*);
	t_vec3		(*get_uv) (t_inter*);
	void		(*f_gui) (void*, void*);
	void		(*export) (int, void*);
};

typedef struct	s_shading {
	t_material	mat;
	t_light		light;
	t_vec3		light_dir;
	float		light_dist;
	t_vec3		hit_pos;
	t_vec3		normal;
	t_vec3		shading_normal;
	t_vec3		specular_dir;
	t_vec3		uv;
}				t_shading;

#endif
