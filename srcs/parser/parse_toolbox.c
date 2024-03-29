/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_toolbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 04:29:28 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "config.h"

t_color
	parse_color(char *key, t_parse_txt *scene_file)
{
	float	toby[3];
	int		idx;
	char	*line;

	idx = -1;
	line = get_args_key_require(scene_file, key);
	while (++idx < 3)
	{
		toby[idx] = ft_atof(line);
		while (*line && *line != ' ' && *line != ')')
			line++;
		while (*line && *line == ' ' && *line != ')')
			line++;
		if (!*line || *line == ')')
			break ;
	}
	if (idx != 2)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_COLOR, scene_file);
	}
	if (DEBUG)
		ft_printf("Color : %f %f %f\n", toby[0], toby[1], toby[2]);
	return ((t_color){toby[0], toby[1], toby[2]});
}

t_vec3
	parse_vector(char *key, t_parse_txt *scene_file)
{
	float	toby[3];
	int		idx;
	char	*line;

	idx = -1;
	line = get_args_key_require(scene_file, key);
	while (++idx < 3)
	{
		toby[idx] = ft_atof(line);
		while (*line && *line != ' ' && *line != ')')
			line++;
		while (*line && *line == ' ' && *line != ')')
			line++;
		if (!*line || *line == ')')
			break ;
	}
	if (idx != 2)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_VEC3, scene_file);
	}
	if (DEBUG)
		ft_printf("Vector : %f %f %f\n", toby[0], toby[1], toby[2]);
	return ((t_vec3){toby[0], toby[1], toby[2]});
}

float
	parse_fval(char *key, t_parse_txt *scene_file)
{
	char	*line;
	float	res;

	line = get_args_key_require(scene_file, key);
	res = ft_atof(line);
	if (DEBUG)
		ft_printf("Float value : %f\n", res);
	return (res);
}

t_vec2
	parse_vec2(char *key, t_parse_txt *scene_file)
{
	float	toby[2];
	int		idx;
	char	*line;

	idx = -1;
	line = get_args_key_require(scene_file, key);
	while (++idx < 2)
	{
		toby[idx] = ft_atof(line);
		while (*line && *line != ' ' && *line != ')')
			line++;
		while (*line && *line == ' ' && *line != ')')
			line++;
		if (!*line || *line == ')')
			break ;
	}
	if (idx != 1)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_VEC2, scene_file);
	}
	if (DEBUG)
		ft_printf("Limit : %f %f\n", toby[0], toby[1]);
	return ((t_vec2){toby[0], toby[1]});
}

int
	parse_int(char *key, t_parse_txt *scene_file)
{
	char	*line;
	int		res;

	line = get_args_key_require(scene_file, key);
	res = ft_atoi(line);
	if (DEBUG)
		ft_printf("Int value : %d\n", res);
	return (res);
}
