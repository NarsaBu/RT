/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:53:12 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	test1(int ac, char **av)
{
	char	**split;

	split = NULL;
	if ((ac == 2) && !(split = ft_strsplit(av[1], 32)))
		return ;
	ft_tabdel(split);
}

void	test2(void)
{
	printf("%f\n", ft_atof("0"));
	printf("%f\n", ft_atof("-0.1"));
	printf("%f\n", ft_atof("-0.100001"));
	printf("%f\n", ft_atof("-0.5"));
	printf("%f\n", ft_atof("0.5"));
	printf("%f\n", ft_atof(" -50"));
	printf("%f\n", ft_atof("50"));
}

int		main(int ac, char **av)
{
	test1(ac, av);
	test2();
	return (0);
}
