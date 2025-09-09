/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/09 22:21:39 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Fait tourner le joueur avec la souris */
void	rotate_player_mouse(t_cub3d *cub3d, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub3d->player.dir_x;
	old_plane_x = cub3d->view.plane_x;
	cub3d->player.dir_x = cub3d->player.dir_x * cos(angle)
		- cub3d->player.dir_y * sin(angle);
	cub3d->player.dir_y = old_dir_x * sin(angle)
		+ cub3d->player.dir_y * cos(angle);
	cub3d->view.plane_x = cub3d->view.plane_x * cos(angle)
		- cub3d->view.plane_y * sin(angle);
	cub3d->view.plane_y = old_plane_x * sin(angle)
		+ cub3d->view.plane_y * cos(angle);
}

/* Gère le mouvement de la souris pour contrôler la vue */
int	handle_mouse_move(int x, int y, t_cub3d *cub3d)
{
	int		delta_x;
	double	rotation_angle;
	double	mouse_sensitivity;

	(void)y;
	if (!cub3d->mouse.captured)
		return (0);
	delta_x = x - cub3d->mouse.last_x;
	if (delta_x == 0)
		return (0);
	mouse_sensitivity = 0.002;
	rotation_angle = delta_x * mouse_sensitivity;
	rotate_player_mouse(cub3d, rotation_angle);
	cub3d->mouse.last_x = x;
	if (x < 50 || x > SCREEN_WIDTH - 50)
	{
		mlx_mouse_move(cub3d->mlx.mlx, cub3d->mlx.win,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		cub3d->mouse.last_x = SCREEN_WIDTH / 2;
	}
	return (0);
}
