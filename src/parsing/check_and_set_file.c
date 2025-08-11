/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_set_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:33:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/11 15:04:18 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_direction(t_cub3d *cub3d, char dir)
{
	if (dir == 'N')
	{
		cub3d->player.dirX = 0;
		cub3d->player.dirY = -1;
	}
	else if (dir == 'S')
	{
		cub3d->player.dirX = 0;
		cub3d->player.dirY = 1;
	}
	else if (dir == 'E')
	{
		cub3d->player.dirX = 1;
		cub3d->player.dirY = 0;
	}
	else if (dir == 'W')
	{
		cub3d->player.dirX = -1;
		cub3d->player.dirY = 0;
	}
}

int	check_and_set_file(t_cub3d *cub3d, char **file)
{
	int	idx_line;
	int	tmp;

	idx_line = 0;
	ft_check_textures(&cub3d->textures, file, &idx_line);
	tmp = idx_line;
	ft_check_colors(&cub3d->colors, file, &idx_line);
	if (tmp > idx_line)
		idx_line = tmp;
	ft_check_map(cub3d, file, &idx_line);
	set_direction(cub3d, cub3d->player.dir);
	cub3d->player.posX = (double)cub3d->player.coords->x + 0.5;
	cub3d->player.posY = (double)cub3d->player.coords->y + 0.5;
	cub3d->player.fov = 66;
	return (1);
}
