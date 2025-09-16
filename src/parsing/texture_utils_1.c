/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 02:09:38 by jdupuis          ###   ########.fr       */
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

int	process_texture_line(t_cub3d *cub3d, int i, int *found_all)
{
	int	j;
	int	result;

	j = 0;
	skip_spaces(cub3d->file[i], &j);
	if (!cub3d->file[i][j])
		return (-1);
	if (!is_letter(cub3d->file[i][j]) && (!all_text_set(cub3d)
		&& !all_colors_set(cub3d)))
	{
		cub3d->invalid_arg = ft_strdup(cub3d->file[i]);
		cub3d->nb_error_line = i;
		exit_error("Invalid line", cub3d);
	}
	if (is_letter(cub3d->file[i][j]))
	{
		result = process_single_texture_line(cub3d, i, found_all);
		return (result);
	}
	return (-1);
}
