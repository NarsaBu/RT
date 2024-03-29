/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 00:15:12 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRT_H
# define LIBRT_H

# include "rtstruct.h"

# define DEG_TO_RAD		(M_PI_F / 180)
# define M_PI_F			(float)M_PI
# define M_INV_PI_F		(1.0f / M_PI_F)

# define EPSILON		1e-6
# define SHADOW_BIAS	5e-2

# define AAAA quad[0]
# define BBBB quad[1]
# define CCCC quad[2]
# define DDDD quad[3]
# define EEEE quad[4]

/*
** Normal :
*/

void		normal_sphere(t_inter *inter);
void		normal_cone(t_inter *inter);
void		normal_cube(t_inter *inter);
void		normal_tore(t_inter *inter);
void		normal_cylinder(t_inter *inter);
void		normal_plane(t_inter *inter);

t_vec3		get_sphere_uv(t_inter *inter);
t_vec3		get_plane_uv(t_inter *inter);
t_vec3		get_cone_uv(t_inter *inter);
t_vec3		get_cube_uv(t_inter *inter);
t_vec3		get_tore_uv(t_inter *inter);
t_vec3		get_cylinder_uv(t_inter *inter);
/*
** Intersection :
*/

void		inter_cylinder(t_inter *data, t_obj *node);
void		inter_plane(t_inter *data, t_obj *node);
void		inter_sphere(t_inter *data, t_obj *node);
void		inter_cone(t_inter *data, t_obj *node);
void		set_min_max_corner(t_cube *cube);
void		inter_cube(t_inter *data, t_obj *node);
void		inter_tore(t_inter *data, t_obj *node);
t_inter		inter_from_csg_op(int type, t_inter left, t_inter right,
			t_ray incoming);
void		inter_csg(t_inter *data, t_obj *node);
void		inter_set(t_inter *inter, t_ray ray);
void		inter_setdeflect(t_inter *inter, t_vec3 shading_normal);
void		inter_setrefract(t_inter *inter, t_ray *res);
void		inter_find(t_inter *primary, t_pt3 *value);
bool		inter_plane_finite(t_inter *data, t_plane *plane, float dist);

/*
** Light :
*/

void		inter_setlight(t_inter *i, t_inter *light_i, t_light *light);

/*
** Vec3 :
*/

void		vec3_find(t_pt3 *origin, t_pt3 *dest, t_vec3 *value);
void		vec3_cpy(t_vec3 *dst, t_vec3 *src);
void		vec3_new(t_vec3 *res, float x, float y, float z);
void		vec3_add(t_vec3 *res, t_vec3 *v1, t_vec3 *v2);
float		vec3_cos(t_vec3 *v1, t_vec3 *v2);
t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2);
void		create_orthobasis_qnd(t_vec3 vec, t_vec3 *t, t_vec3 *b);
float		vec3_dot(t_vec3 *v1, t_vec3 *v2);
float		vec3_mag(t_vec3 v1);
void		vec3_normalize(t_vec3 *v1);
t_vec3		vec3_normalize_(t_vec3 v1);
void		vec3_print(t_vec3 *data);
void		vec3_print_(char *msg, t_vec3 data);
void		vec3_scalar(t_vec3 *v1, float k);
void		vec3_sub(t_vec3 *res, t_vec3 *v1, t_vec3 *v2);
t_vec3		vec3_sub_(t_vec3 a, t_vec3 b);
void		vec3_mul(t_vec3 *res, t_vec3 *v1, t_vec3 *v2);
t_vec3		vec3_mul_(t_vec3 a, t_vec3 b);
t_vec3		vec3_deflect(t_vec3 vec, t_vec3 normal);
t_vec3		vec3_refract(t_vec3 ray, t_vec3 normal, float ior);
void		vec3_cartesian_to_spherical(t_vec3 v, float *azimuth, float *polar);
void		vec3_matrix_camera(t_matrix *matrix, t_cam *cam);
void		vec3_matrix_mult(t_matrix *matrix, t_matrix *add);
t_matrix	matrix_mult(const t_matrix *lhs, const t_matrix *rhs);
t_matrix	mat_orbit(t_vec3 axis, float deg);
t_vec3		get_column(t_matrix m, int column);
void		set_column(t_matrix *m, int column, t_vec3 vec);
void		set_row(t_matrix *m, int row, t_vec3 vec);
t_matrix	mat_set_axes(t_vec3 x, t_vec3 y, t_vec3 z);
void		mat_transpose(t_matrix *m);
void		apply_matrix(t_vec3 *v, t_matrix *mat);
void		ray_new(t_ray *res, t_pt3 *origin, t_vec3 *n);
void		print_matrix(t_matrix *mat);
void		mat3_rot(t_matrix *mat_x, t_matrix *mat_y, t_vec3 *vi, t_cam *cam);
void		create_orthobasis_from_y_axis(t_vec3 y, t_vec3 *x, t_vec3 *z);
t_matrix	set_rotation(float yz_angle, float xz_angle);
float		fresnel(t_vec3 ray_dir, t_vec3 normal, float ior);
void		ray_offset_origin(t_ray *ray, t_vec3 normal);
t_ray		ray_transform(t_ray ray, t_matrix m);
void		apply_uv_mapping(t_vec3 *uv, t_uv_mapping mapping);
float		remap_to_0_to_1(float x);

#endif
