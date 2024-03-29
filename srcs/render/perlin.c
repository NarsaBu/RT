/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:34:53 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:56:06 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "perlin.h"

float
	lerp(float a, float b, float t)
{
	return ((1.0 - t) * a + t * b);
}

float
	grad(int hash, float x, float y, float z)
{
	int		h;
	float	u;
	float	v;

	h = hash & 15;
	u = (h < 8) ? x : y;
	if (h < 4)
		v = y;
	else if (h == 12 || h == 14)
		v = x;
	else
		v = z;
	return (((h & 1) == 0) ? u : -u) + (((h & 2) == 0) ? v : -v);
}

void
	permutation_table(float x, float y, float z, int res[8])
{
	int xi;
	int	yi;
	int	zi;

	xi = (int)x & 255;
	yi = (int)y & 255;
	zi = (int)z & 255;
	res[0] = g_perm[(g_perm[(g_perm[xi] + yi) % 256] + zi) % 256];
	res[1] = g_perm[(g_perm[(g_perm[xi] + yi + 1) % 256] + zi) % 256];
	res[2] = g_perm[(g_perm[(g_perm[xi] + yi) % 256] + zi + 1) % 256];
	res[3] = g_perm[(g_perm[(g_perm[xi] + yi + 1) % 256] + zi + 1) % 256];
	res[4] = g_perm[(g_perm[(g_perm[xi + 1] + yi) % 256] + zi) % 256];
	res[5] = g_perm[(g_perm[(g_perm[xi + 1] + yi + 1) % 256] + zi) % 256];
	res[6] = g_perm[(g_perm[(g_perm[xi + 1] + yi) % 256] + zi + 1) % 256];
	res[7] = g_perm[(g_perm[(g_perm[xi + 1] + yi + 1) % 256] + zi + 1) % 256];
}

float
	noise(float x, float y, float z)
{
	t_perlin	env;

	permutation_table(x, y, z, env.l_perm);
	env.xf = x - (int)x;
	env.yf = y - (int)y;
	env.zf = z - (int)z;
	env.u = (env.xf * env.xf * env.xf * (env.xf * (env.xf * 6 - 15) + 10));
	env.v = (env.yf * env.yf * env.yf * (env.yf * (env.yf * 6 - 15) + 10));
	env.w = (env.zf * env.zf * env.zf * (env.zf * (env.zf * 6 - 15) + 10));
	env.x1 = lerp(grad(env.l_perm[0], env.xf, env.yf, env.zf),
		grad(env.l_perm[4], env.xf - 1, env.yf, env.zf), env.u);
	env.x2 = lerp(grad(env.l_perm[1], env.xf, env.yf - 1, env.zf),
		grad(env.l_perm[5], env.xf - 1, env.yf - 1, env.zf), env.u);
	env.y1 = lerp(env.x1, env.x2, env.v);
	env.x1 = lerp(grad(env.l_perm[2], env.xf, env.yf, env.zf - 1),
		grad(env.l_perm[6], env.xf - 1, env.yf, env.zf - 1), env.u);
	env.x2 = lerp(grad(env.l_perm[3], env.xf, env.yf - 1, env.zf - 1),
		grad(env.l_perm[7], env.xf - 1, env.yf - 1, env.zf - 1), env.u);
	env.y2 = lerp(env.x1, env.x2, env.v);
	return (lerp(env.y1, env.y2, env.w));
}

float
	perlin(t_vec3 uv, int octaves, float persistence)
{
	int		i;
	float	total;
	float	freq;
	float	amplitude;
	float	coef;

	i = 0;
	total = 0;
	freq = 1;
	amplitude = 1;
	coef = 0;
	while (i < octaves)
	{
		total += noise(uv.x * freq, uv.y * freq, uv.z * freq) * amplitude;
		coef += amplitude;
		amplitude *= persistence;
		freq *= 2;
		i++;
	}
	return (total / coef);
}
