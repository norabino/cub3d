/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:19:02 by norabino          #+#    #+#             */
/*   Updated: 2025/08/20 16:05:01 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Initialise MinilibX et prépare l'affichage
** Crée la fenêtre, prépare l'image pour dessiner dessus
** Charge toutes les textures des murs
** C'est comme préparer une toile et ses pinceaux avant de peindre
*/
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
	load_all_textures(cub3d);
	return (cub3d);
}
