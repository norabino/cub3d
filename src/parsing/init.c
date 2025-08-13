/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:24:01 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/11 19:45:28 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init(t_cub3d *cub3d)
{
	int	i;

	cub3d->mlx.mlx = NULL;
	cub3d->mlx.img = NULL;
	cub3d->mlx.win = NULL;
	cub3d->player.coords = malloc(sizeof(t_point));
	cub3d->player.coords->x = -1;
	cub3d->player.coords->y = -1;
	cub3d->player.coords->direction = 0;
	cub3d->player.coords->cub3d = cub3d;
	cub3d->textures.north = NULL;
	cub3d->textures.south = NULL;
	cub3d->textures.west = NULL;
	cub3d->textures.east = NULL;
	cub3d->textures.cub3d = cub3d;
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
}
