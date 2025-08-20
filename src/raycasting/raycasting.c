/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/20 15:37:38 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Cast single ray for one screen column */
void	cast_single_ray(t_cub3d *cub3d, int screen_x)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	perp_wall_dist;
	t_dda	dda;

	if (!cub3d || screen_x < 0 || screen_x >= SCREEN_WIDTH)
		return ;
	camera_x = 2 * screen_x / (double)SCREEN_WIDTH - 1;
	ray_dir_x = cub3d->player.dir_x + cub3d->view.plane_x * camera_x;
	ray_dir_y = cub3d->player.dir_y + cub3d->view.plane_y * camera_x;
	init_dda_params(cub3d, ray_dir_x, ray_dir_y, &dda);
	dda.ray_dir_x = ray_dir_x;
	dda.ray_dir_y = ray_dir_y;
	init_step_and_side_dist(&dda, ray_dir_x, ray_dir_y, cub3d);
	perform_dda_algorithm(cub3d, &dda);
	perp_wall_dist = calc_perpendicular_wall_distance(&dda, ray_dir_x,
			ray_dir_y, cub3d);
	draw_wall_slice(cub3d, screen_x, perp_wall_dist, &dda);
}

/* Main raycast function - renders entire screen */
void	raycast(t_cub3d *cub3d)
{
	int	x;

	if (!cub3d || !cub3d->mlx.mlx || !cub3d->mlx.img)
		return ;
	calc_camera_plane(cub3d);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cast_single_ray(cub3d, x);
		x++;
	}
}
