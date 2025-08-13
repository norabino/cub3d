/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/13 16:07:12 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Initialize DDA parameters for ray calculation */
void	init_dda_params(t_cub3d *cub3d, double ray_dir_x, double ray_dir_y,
	t_dda *dda)
{
	if (!cub3d || !dda)
		return ;
	dda->map_x = cub3d->player.posX;
	dda->map_y = cub3d->player.posY;
	if (ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1.0 / ray_dir_y);
	dda->hit = 0;
}

/* Calculate step direction and initial side distances */
void	init_step_and_side_dist(t_dda *dda, double ray_dir_x,
	double ray_dir_y, t_cub3d *cub3d)
{
	double	map_x;

	if (!dda || !cub3d)
		return ;
	map_x = cub3d->player.posX;
	if (ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (cub3d->player.posX - map_x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (map_x + 1.0 - cub3d->player.posX)
			* dda->delta_dist_x;
	}
	init_step_and_side_dist_y(dda, ray_dir_y, cub3d);
}

/* Helper function for init_step_and_side_dist (y direction) */
void	init_step_and_side_dist_y(t_dda *dda, double ray_dir_y,
	t_cub3d *cub3d)
{
	double	map_y;

	map_y = cub3d->player.posY;
	if (ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (cub3d->player.posY - map_y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (map_y + 1.0 - cub3d->player.posY)
			* dda->delta_dist_y;
	}
}

/* Perform DDA algorithm to find wall hit */
void	perform_dda_algorithm(t_cub3d *cub3d, t_dda *dda)
{
	int	max_iterations;

	if (!cub3d || !dda || !cub3d->map)
		return ;
	max_iterations = 1000;
	while (dda->hit == 0 && max_iterations-- > 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if ((int)dda->map_y >= 0 && (int)dda->map_x >= 0
			&& cub3d->map[(int)dda->map_y]
			&& cub3d->map[(int)dda->map_y][(int)dda->map_x] == '1')
			dda->hit = 1;
	}
}

/* Calculate perpendicular wall distance */
double	calc_perpendicular_wall_distance(t_dda *dda, double ray_dir_x,
	double ray_dir_y, t_cub3d *cub3d)
{
	double	perp_wall_dist;

	if (dda->side == 0)
		perp_wall_dist = (dda->map_x - cub3d->player.posX
				+ (1 - dda->step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (dda->map_y - cub3d->player.posY
				+ (1 - dda->step_y) / 2) / ray_dir_y;
	return (perp_wall_dist);
}
