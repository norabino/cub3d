/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/22 18:55:03 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	texture_duplicate(char c, t_cub3d *cub3d)
{
	if (c == 'N')
		exit_error("Duplicate north texture", cub3d);
	else if (c == 'S')
		exit_error("Duplicate south texture", cub3d);
	else if (c == 'W')
		exit_error("Duplicate west texture", cub3d);
	else if (c == 'E')
		exit_error("Duplicate east texture", cub3d);
	else if (c == 'F')
		exit_error("Duplicate floor texture", cub3d);
	else if (c == 'C')
		exit_error("Duplicate ceiling texture", cub3d);
	else if (c == 'P')
		exit_error("Duplicate portal folder", cub3d);
}

int	parse_texture_line(t_cub3d *cub3d, int i)
{
	int		j;
	int		z;

	j = 0;
	skip_spaces(cub3d->file[i], &j);
	if ((cub3d->file[i][j] == 'N' && cub3d->textures.north)
		|| (cub3d->file[i][j] == 'S' && cub3d->textures.south)
		|| (cub3d->file[i][j] == 'W' && cub3d->textures.west)
		|| (cub3d->file[i][j] == 'E' && cub3d->textures.east)
		|| (cub3d->file[i][j] == 'F' && cub3d->textures.floor)
		|| (cub3d->file[i][j] == 'C' && cub3d->textures.ceiling)
		|| (cub3d->file[i][j] == 'P' && cub3d->textures.portals))
		texture_duplicate(cub3d->file[i][j], cub3d);
	z = j;
	j += skip_letter(cub3d->file[i][j], cub3d->file[i][j + 1]);
	skip_spaces(cub3d->file[i], &j);
	if (check_path(cub3d->file[i], j))
		process_texture_path_found(cub3d, j, z, i);
	return (i);
}
