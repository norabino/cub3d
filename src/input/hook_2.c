/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:31:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 18:13:30 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Boucle principale du jeu qui s'exécute en continu */
int	handle_loop(t_cub3d *cub3d)
{
	long	current_time;

	if (!cub3d || !cub3d->mlx.mlx || !cub3d->mlx.win || !cub3d->mlx.img)
		return (0);
	
	current_time = gettime_ms();
	if ((current_time - cub3d->time.last_refresh) >= (1000 / FPS))
	{
		update_delta_time_from_timestamp(cub3d, current_time);
		handle_movement(cub3d);
		handle_direction(cub3d);
		check_any_key_pressed(cub3d);
		if (cub3d->nb_portals > 0)
			update_portal_animations(cub3d);
		cub3d->time.last_refresh = current_time;
		calculate_fps(cub3d);
		refresh_image(cub3d);
	}
	return (0);
}

/* Vérifie si une touche du clavier est actuellement pressée */
int	check_any_key_pressed(t_cub3d *cub3d)
{
	int	i;

	if (!cub3d)
		return (0);
	i = 0;
	while (i < 256)
	{
		if (cub3d->input_state[i])
			return (1);
		i++;
	}
	return (0);
}

/* Rafraîchit l'image à l'écran */
void	refresh_image(t_cub3d *cub3d)
{
	if (!cub3d || !cub3d->mlx.mlx || !cub3d->mlx.win || !cub3d->mlx.img)
		return ;
	if (!cub3d->mlx.img->img)
		return ;
	raycast(cub3d);
	render_sprites(cub3d);
	draw_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win,
		cub3d->mlx.img->img, 0, 0);
	display_fps(cub3d);
}
