/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 03:28:01 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 10:56:06 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "t_data.h"
#include "interface.h"

bool
	check_file(char *filename)
{
	int fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (false);
	close(fd);
	return (true);
}

void
	reload_scene(t_data *app, char *filename)
{
	char *tmp;

	if (ft_strcmp(filename, "scenes/") == 0)
	{
		ft_strlcpy(app->gui.err_msg, "Can't reload an unsaved scene.",
			sizeof(app->gui.err_msg));
		app->gui.err_open = true;
		return ;
	}
	if (!(tmp = ft_strdup(filename)))
		ft_error(__func__, __LINE__);
	load_scene(app, tmp);
	ft_strdel(&tmp);
}
