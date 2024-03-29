/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itocolor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 20:28:46 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:48:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color
	itocolor(int color)
{
	t_color c;

	c.r = (color >> SHIFT_RED) & 0xFF;
	c.g = (color >> SHIFT_GREEN) & 0xFF;
	c.b = (color >> SHIFT_BLUE) & 0xFF;
	color_scalar(&c, 1 / 255.f);
	return (c);
}
