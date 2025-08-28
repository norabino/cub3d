/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_set_file_clean.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:33:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/28 22:00:59 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_direction(t_cub3d *cub3d, char dir)
{
	if (dir == 'N')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = -1;
	}
	else if (dir == 'S')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = 1;
	}
	else if (dir == 'E')
	{
		cub3d->player.dir_x = 1;
		cub3d->player.dir_y = 0;
	}
	else if (dir == 'W')
	{
		cub3d->player.dir_x = -1;
		cub3d->player.dir_y = 0;
	}
}

int	check_and_set_file(t_cub3d *cub3d, char **file)
{
	int	idx_line;
	int	tmp;

	tmp = 0;
	if (!file)
		return (0);
	idx_line = check_textures(cub3d, file);
	if (idx_line == -1)
		return (0);
	idx_line = check_colors(cub3d, file, idx_line);
	if (idx_line == -1)
		return (0);
	cub3d->map = get_map(file, idx_line);
	if (!cub3d->map)
		return (0);
	tmp = check_map(cub3d);
	set_prtls(cub3d);
	init_prtl_sprites(cub3d);
	return (tmp);
}
