/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:19:02 by norabino          #+#    #+#             */
/*   Updated: 2025/09/09 22:19:01 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Initialise MinilibX et prépare l'affichage */
void	init_minilibx(t_cub3d *cub3d)
{
	cub3d->mlx.img = malloc(sizeof(t_img));
	cub3d->mlx.mlx = mlx_init();
	cub3d->mlx.win = mlx_new_window(cub3d->mlx.mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (!cub3d->mlx.win)
		exit_error("no window", cub3d);
	cub3d->mlx.img->img = mlx_new_image(cub3d->mlx.mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!cub3d->mlx.img->img)
	{
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
		exit_error("no image", cub3d);
	}
	cub3d->mlx.img->addr = mlx_get_data_addr(cub3d->mlx.img->img,
			&cub3d->mlx.img->bits_per_pixel, &cub3d->mlx.img->line_length,
			&cub3d->mlx.img->endian);
	load_all_textures(cub3d);
	if (cub3d->nb_portals > 0)
		init_prtl_sprites(cub3d);
}
