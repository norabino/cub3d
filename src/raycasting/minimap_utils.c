/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/26 20:50:03 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Vérifie si une position est un mur dans la carte
** Optimisé avec vérifications early-exit
*/
int	is_wall_at_pos(t_cub3d *cub3d, double world_x, double world_y)
{
	if (world_x < 0 || world_y < 0)
		return (0);
	if ((int)world_y >= ft_tablen(cub3d->map))
		return (0);
	if (!cub3d->map[(int)world_y])
		return (0);
	if ((int)world_x >= ft_strlen(cub3d->map[(int)world_y]))
		return (0);
	return (cub3d->map[(int)world_y][(int)world_x] == '1');
}

/*
** Calcule la position mondiale à partir des coordonnées d'écran
** Optimisé: pré-calcule cos et sin pour éviter les appels répétés
*/
void	calculate_world_pos(double *world_x, double *world_y,
	t_minimap_calc *calc, t_minimap_screen *screen)
{
	double	relative_x;
	double	relative_y;

	relative_x = (double)screen->x / MINIMAP_SCALE;
	relative_y = (double)screen->y / MINIMAP_SCALE;
	*world_x = calc->player_x + (relative_x * calc->cos_angle
			- relative_y * calc->sin_angle);
	*world_y = calc->player_y + (relative_x * calc->sin_angle
			+ relative_y * calc->cos_angle);
}

/*
** Initialise les calculs pour la minimap
** Optimisé: pré-calcule l'angle et les fonctions trigonométriques
*/
void	init_minimap_calc(t_cub3d *cub3d, t_minimap_calc *calc)
{
	double	player_angle;

	calc->player_x = cub3d->player.pos_x;
	calc->player_y = cub3d->player.pos_y;
	player_angle = atan2(cub3d->player.dir_y, cub3d->player.dir_x) + M_PI / 2;
	calc->cos_angle = cos(player_angle);
	calc->sin_angle = sin(player_angle);
}

/*
** Fait tourner un point autour de l'origine de manière intuitive
** Fonction legacy maintenue pour compatibilité
*/
void	rotate_point(double *x, double *y, double angle)
{
	double	old_x;
	double	old_y;

	old_x = *x;
	old_y = *y;
	*x = old_x * cos(-angle) - old_y * sin(-angle);
	*y = old_x * sin(-angle) + old_y * cos(-angle);
}

/*
** Dessine un pixel de la minimap avec opacité selon sa distance du centre
** Utilise un vrai alpha blending avec les textures existantes
** Optimisé: calcul de distance optimisé avec early exit
*/
void	draw_minimap_pixel(t_cub3d *cub3d, int x, int y, int radius)
{
	int	dx;
	int	dy;
	int	dist_sq;
	int	existing_color;
	int	blended_color;

	dx = x - (MINIMAP_X + MINIMAP_SIZE / 2);
	dy = y - (MINIMAP_Y + MINIMAP_SIZE / 2);
	dist_sq = dx * dx + dy * dy;
	if (dist_sq <= radius * radius)
	{
		if (dist_sq <= (radius - 2) * (radius - 2))
		{
			existing_color = get_pixel_color(cub3d->mlx.img, x, y);
			blended_color = alpha_blend(existing_color, 0x808080, 0.7);
			my_mlx_pixel_put(cub3d->mlx.img, x, y, blended_color);
		}
		else
			my_mlx_pixel_put(cub3d->mlx.img, x, y, MINIMAP_COLOR_BORDER);
	}
}
