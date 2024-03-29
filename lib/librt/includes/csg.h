/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:02:52 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:48:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSG_H
# define CSG_H

# include "rtstruct.h"

typedef struct	s_csg_op
{
	int			type;
}				t_csg_op;

typedef struct s_inter_csg	t_inter_csg;

struct			s_inter_csg
{
	t_inter		inter;
	t_inter_csg	*next;
};

bool			is_inside_cone(t_inter *inter);
t_inter			not_plane(t_inter core, t_inter sub);

#endif
