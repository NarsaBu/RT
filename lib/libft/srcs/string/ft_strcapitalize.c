/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 10:19:57 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include "ftctype.h"
#include "ftstring.h"
#include "ftconvert.h"

inline static int	ft_caprule(char c)
{
	return (ft_btw(c, 31, 47) || ft_btw(c, 58, 64) || ft_isspace(c));
}

char				*ft_strcapitalize(char *str)
{
	char *pstr;

	pstr = ft_strlowcase(str);
	if (*pstr)
	{
		*pstr = (char)ft_toupper(*pstr);
		pstr++;
	}
	while (*pstr)
	{
		if (ft_caprule(*(pstr - 1)))
			*pstr = (char)ft_toupper(*pstr);
		pstr++;
	}
	return (str);
}
