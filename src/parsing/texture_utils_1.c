/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/17 22:04:28 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	assign_texture(char c, char *sub, t_cub3d *cub3d)
{
	if (c == 'N' && !cub3d->textures.north)
		cub3d->textures.north = sub;
	else if (c == 'S' && !cub3d->textures.south)
		cub3d->textures.south = sub;
	else if (c == 'W' && !cub3d->textures.west)
		cub3d->textures.west = sub;
	else if (c == 'E' && !cub3d->textures.east)
		cub3d->textures.east = sub;
	else if (c == 'P' && !cub3d->textures.portals)
		cub3d->textures.portals = sub;
	else if (c == 'F' && !cub3d->textures.floor)
		cub3d->textures.floor = sub;
	else if (c == 'C' && !cub3d->textures.ceiling)
		cub3d->textures.ceiling = sub;
	else
	{
		free(sub);
		exit_error("Duplicate or invalid texture identifier.", cub3d);
	}
}

int	process_texture_line(t_cub3d *cub3d, int i)
{
	int	j;
	int	result;

	j = 0;
	skip_spaces(cub3d->file[i], &j);
	if (!cub3d->file[i][j])
		return (-1);
	if (is_letter(cub3d->file[i][j]))
	{
		result = parse_texture_line(cub3d, i);
		return (result + 1);
	}
	return (-1);
}

int	process_color_line(t_cub3d *cub3d, int i)
{
	int	j;
	int	result;

	j = 0;
	skip_spaces(cub3d->file[i], &j);
	if (!cub3d->file[i][j])
		return (-1);
	if (is_letter(cub3d->file[i][j]))
	{
		result = parse_color_line(cub3d, i);
		return (result + 1);
	}
	return (-1);
}
