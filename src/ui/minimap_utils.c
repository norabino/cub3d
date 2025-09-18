/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 20:14:47 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Vérifie si une position est un portail dans la carte */
int	is_portal_at_pos(t_cub3d *cub3d, double world_x, double world_y)
{
	if (world_x < 0 || world_y < 0)
		return (0);
	if ((int)world_y >= ft_tablen(cub3d->map))
		return (0);
	if (!cub3d->map[(int)world_y])
		return (0);
	if ((int)world_x >= ft_strlen(cub3d->map[(int)world_y]))
		return (0);
	return (is_lowercase(cub3d->map[(int)world_y][(int)world_x]));
}

/* Calcule la position mondiale à partir des coordonnées d'écran */
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

/* Initialise les calculs pour la minimap */
void	init_minimap_calc(t_cub3d *cub3d, t_minimap_calc *calc)
{
	double	player_angle;

	calc->player_x = cub3d->player.pos_x;
	calc->player_y = cub3d->player.pos_y;
	player_angle = atan2(cub3d->player.dir_y, cub3d->player.dir_x) + PI / 2;
	calc->cos_angle = cos(player_angle);
	calc->sin_angle = sin(player_angle);
}

/* Vérifie si un point est dans le cercle de la minimap */
int	is_point_in_circle(int x, int y, int radius)
{
	int	dx;
	int	dy;

	dx = x;
	dy = y;
	return (dx * dx + dy * dy <= radius * radius);
}
