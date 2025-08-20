/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:24:01 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/20 15:28:20 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Initialize cub3d structure part 1 */
static void	init_basic_values(t_cub3d *cub3d)
{
	cub3d->mlx.mlx = NULL;
	cub3d->mlx.img = NULL;
	cub3d->mlx.win = NULL;
	cub3d->player.direction = 0;
	cub3d->player.cub3d = cub3d;
	cub3d->textures.north = NULL;
	cub3d->textures.south = NULL;
	cub3d->textures.west = NULL;
	cub3d->textures.east = NULL;
	cub3d->textures.cub3d = cub3d;
}

/* Initialize cub3d structure part 2 */
static void	init_colors_and_keys(t_cub3d *cub3d)
{
	int	i;

	cub3d->colors.floor[0] = -1;
	cub3d->colors.floor[1] = -1;
	cub3d->colors.floor[2] = -1;
	cub3d->colors.ceiling[0] = -1;
	cub3d->colors.ceiling[1] = -1;
	cub3d->colors.ceiling[2] = -1;
	cub3d->colors.cub3d = cub3d;
	cub3d->player.fov = 0;
	ft_strcpy(cub3d->alpha, "abcdefghijklmnopqrstuvwxyz");
	cub3d->map = NULL;
	i = 0;
	while (i < 256)
	{
		cub3d->keys[i] = 0;
		i++;
	}
	cub3d->last_refresh = 0;
}

void	init(t_cub3d *cub3d)
{
	init_basic_values(cub3d);
	init_colors_and_keys(cub3d);
}
