/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:31:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/11 19:32:23 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_loop(t_cub3d *cub3d)
{
	int	movement_made;

	if (!cub3d || !cub3d->mlx.mlx || !cub3d->mlx.win || !cub3d->mlx.img)
		return (0);
	movement_made = 0;
	movement_made += handle_movement(cub3d);
	movement_made += handle_direction(cub3d);
	if (movement_made)
	{
		if (cub3d->mlx.img->img)
			mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.img->img);
		cub3d->mlx.img->img = mlx_new_image(cub3d->mlx.mlx, 1280, 720);
		if (!cub3d->mlx.img->img)
			return (0);
		cub3d->mlx.img->addr = mlx_get_data_addr(cub3d->mlx.img->img,
				&cub3d->mlx.img->bits_per_pixel,
				&cub3d->mlx.img->line_length, &cub3d->mlx.img->endian);
		raycast(cub3d);
		mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win,
			cub3d->mlx.img->img, 0, 0);
	}
	return (0);
}
