/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 09:14:13 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>
# include <stdbool.h>

# define SHIFT_RED		16
# define SHIFT_GREEN	8
# define SHIFT_BLUE		0

typedef struct	s_color
{
	float		r;
	float		g;
	float		b;
}				t_color;

void			color_mult(t_color *color, t_color *mult);
t_color			color_mult_(t_color color, t_color mult);
void			color_scalar(t_color *color, float k);
t_color			color_scalar_(t_color color, float k);
void			color_add(t_color *color, t_color add);
t_color			color_add_(t_color color, t_color add);
t_color			color_sub(t_color color, t_color sub);
void			color_max(t_color *col1, t_color *col2);
void			color_clamp(t_color *color, float min, float max);
bool			color_bool(t_color color);
t_color			itocolor(int color);
int				colortoi(t_color color);
t_color			color_linear_inter(t_color color0, t_color color1, float value);

#endif
