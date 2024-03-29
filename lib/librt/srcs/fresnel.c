/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:56:28 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:48:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "libft.h"
#include <math.h>

float	fresnel(t_vec3 ray_dir, t_vec3 normal, float ior)
{
	float	quad[5];
	float	res[2];

	if (ior == 0)
		return (1);
	vec3_scalar(&ray_dir, -1);
	AAAA = ft_clampf(vec3_dot(&ray_dir, &normal), -1, 1);
	BBBB = 1;
	CCCC = ior;
	if (AAAA < 0)
		ft_swapf(&BBBB, &CCCC);
	DDDD = BBBB / CCCC * sqrtf(fmaxf(0.f, 1 - AAAA * AAAA));
	if (DDDD >= 1 && AAAA < 0)
		return (1);
	else
	{
		EEEE = sqrtf(fmaxf(0.f, 1 - DDDD * DDDD));
		AAAA = fabsf(AAAA);
		res[0] = ((CCCC * AAAA - BBBB * EEEE) / (CCCC * AAAA + BBBB * EEEE));
		res[1] = ((BBBB * AAAA - CCCC * EEEE) / (BBBB * AAAA + CCCC * EEEE));
		return (res[0] * res[0] + res[1] * res[1]) / 2;
	}
}

/*
** void fresnel(const Vec3f &I, const Vec3f &N, const float &ior, float &kr)
** {
**     float cosi = clamp(-1, 1, dotProduct(I, N));
**     float etai = 1, etat = ior;
**     if (cosi > 0)
**		{
** 			std::swap(etai, etat); }
**     // Compute sini using Snell's law
**     float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
**     // Total internal reflection
**     if (sint >= 1) {
**         kr = 1;
**     }
**     else {
**         float cost = sqrtf(std::max(0.f, 1 - sint * sint));
**         cosi = fabsf(cosi);
**         float Rs = (etat * cosi - etai * cost) / (etat * cosi + etai * cost);
**         float Rp = (etai * cosi - etat * cost) / (etai * cosi + etat * cost);
**         kr = (Rs * Rs + Rp * Rp) / 2;
**     }
**	As a consequence of the conservation of energy, transmittance is given by:
**	kt = 1 - kr;
** }
*/
