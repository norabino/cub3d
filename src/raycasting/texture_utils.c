/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/20 16:05:01 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define SCREEN_HEIGHT 720

/*
** Calcule à quelle vitesse on doit avancer dans la texture
** Comme calculer de combien de centimètres avancer sur le poster
** pour chaque pixel qu'on dessine à l'écran
*/
void	calc_texture_step_pos(t_texture_calc *tex_calc, int draw_start)
{
	int		real_wall_height;
	int		tex_height;

	real_wall_height = (int)(SCREEN_HEIGHT / tex_calc->perp_wall_dist);
	tex_height = tex_calc->current_texture->height;
	tex_calc->step = (double)tex_height / real_wall_height;
	tex_calc->tex_pos = (draw_start - SCREEN_HEIGHT / 2
			+ real_wall_height / 2) * tex_calc->step;
}

/*
** Prépare tous les paramètres avant de dessiner
** Comme préparer ses pinceaux et couleurs avant de peindre
*/
void	init_texture_draw_params(t_texture_calc *tex_calc,
	int draw_params[2], int *tex_height, int *draw_bounds[2])
{
	draw_bounds[0] = &draw_params[0];
	draw_bounds[1] = &draw_params[1];
	calc_texture_step_pos(tex_calc, *draw_bounds[0]);
	*tex_height = tex_calc->current_texture->height;
}

/*
** Dessine UN SEUL pixel avec la bonne couleur de texture
** Prend la couleur du poster et la met sur l'écran au bon endroit
** S'assure que la couleur existe bien et n'est pas hors limites
*/
void	draw_single_texture_pixel(t_cub3d *cub3d, int screen_x, int y,
	t_texture_calc *tex_calc)
{
	int	color;

	tex_calc->tex_y = (int)tex_calc->tex_pos;
	if (tex_calc->tex_y >= tex_calc->current_texture->height)
		tex_calc->tex_y = tex_calc->current_texture->height - 1;
	else if (tex_calc->tex_y < 0)
		tex_calc->tex_y = 0;
	tex_calc->tex_pos += tex_calc->step;
	color = get_texture_pixel_color(tex_calc->current_texture,
			tex_calc->tex_x, tex_calc->tex_y);
	my_mlx_pixel_put(cub3d->mlx.img, screen_x, y, color);
}
