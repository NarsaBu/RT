/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:10:22 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftgnl.h"
#include "ftstring.h"
#include "ftmath.h"
#include <unistd.h>

/*
** This functions fetch a packet and return how many byte has been read.
*/

inline static ssize_t	ft_fetchpacket(int const fd, char **flux)
{
	ssize_t	byte_read;
	char	*packet;

	if (!(packet = ft_strnew(BUFF_SIZE)))
		return (-1);
	byte_read = read(fd, packet, BUFF_SIZE);
	if (!(*flux = ft_strjoinfree(*flux, packet)))
		return (-1);
	ft_strdel(&packet);
	return (byte_read);
}

/*
** Read from the t_gnl struct & handle the data.
** 1:	Find an '\n' in the node.save, if not found fetch a packet in loop.
** 10:	Populate line & sub the data taken in the node.
** 11:	Handle the return value.
*/

inline static int		process_line(t_gnl *node, char **line, char *endlsep)
{
	ssize_t	read_byte;
	size_t	lenendl;
	size_t	len_s;
	char	*endl;

	read_byte = 1;
	while (!(endl = ft_strpbrk(node->save, endlsep)) && read_byte > 0)
		read_byte = ft_fetchpacket(node->fd, &node->save);
	len_s = ft_strlen(node->save);
	lenendl = (endl == NULL) ? len_s : (size_t)(endl - node->save);
	if (!(*line = ft_strndup(node->save, lenendl)))
		return (-1);
	if (!(node->save = ft_strsubfree(node->save, lenendl + 1, len_s - lenendl)))
		return (-1);
	return (len_s > 0 || lenendl > 0 || read_byte > 0);
}

/*
** Hold the data list, handle errors.
*/

int						ft_gnl(int const fd, char **line, char *endl)
{
	static t_gnl	memory[MAX_FD + 1];
	char			errfd[1];
	int				ret;

	if (!(ft_btw(fd, 0, MAX_FD) && ft_btw(BUFF_SIZE, 0, MAX_BS)))
		return (-1);
	if (line == NULL || read(fd, errfd, 0) == -1)
		return (-1);
	if (memory[fd].save == NULL)
	{
		memory[fd].fd = fd;
		if (!(memory[fd].save = ft_strnew(0)))
			return (-1);
	}
	ret = process_line(&memory[fd], line, endl);
	if (ret == 0)
	{
		ft_strdel(&memory[fd].save);
		ft_strdel(line);
	}
	return (ret);
}
