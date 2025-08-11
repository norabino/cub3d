/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:19:02 by norabino          #+#    #+#             */
/*   Updated: 2025/07/30 15:53:56 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_cub3d	*init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx.img = malloc(sizeof(t_img));
	cub3d->mlx.mlx = mlx_init();
	cub3d->mlx.win = mlx_new_window(cub3d->mlx.mlx, 1280, 720, "CUB3D");
	if (!cub3d->mlx.win)
		exit_error("no window", cub3d);
	cub3d->mlx.img->img = mlx_new_image(cub3d->mlx.mlx, 1280, 720);
	if (!cub3d->mlx.img->img)
	{
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
		exit_error("no img", cub3d);
	}
	cub3d->mlx.img->addr = mlx_get_data_addr(cub3d->mlx.img->img,
			&cub3d->mlx.img->bits_per_pixel, &cub3d->mlx.img->line_length,
			&cub3d->mlx.img->endian);
	return (cub3d);
}