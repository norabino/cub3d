/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/22 18:56:09 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_dda_params(t_cub3d *cub3d, double ray_dir_x, double ray_dir_y,
	t_dda *dda)
{
	if (!dda)
		return ;
	dda->map_x = (int)cub3d->player.pos_x;
	dda->map_y = (int)cub3d->player.pos_y;
	if (ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = ft_abs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = ft_abs(1.0 / ray_dir_y);
	dda->hit = 0;
}

/* Calcule la direction et les distances initiales pour DDA */
void	init_step_and_side_dist(t_dda *dda, double ray_dir_x,
	double ray_dir_y, t_cub3d *cub3d)
{
	int	map_x;

	map_x = (int)cub3d->player.pos_x;
	if (ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (cub3d->player.pos_x - map_x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (map_x + 1 - cub3d->player.pos_x)
			* dda->delta_dist_x;
	}
	init_step_and_side_dist_y(dda, ray_dir_y, cub3d);
}

/* Calcule les paramètres de pas et distance pour la direction Y */
void	init_step_and_side_dist_y(t_dda *dda, double ray_dir_y,
	t_cub3d *cub3d)
{
	int	map_y;

	map_y = (int)cub3d->player.pos_y;
	if (ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (cub3d->player.pos_y - map_y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (map_y + 1.0 - cub3d->player.pos_y)
			* dda->delta_dist_y;
	}
}

void	perform_dda_algorithm(t_cub3d *cub3d, t_dda *dda)
{
	int	max_iterations;

	if (!cub3d->map)
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
		if (dda->map_y >= 0 && dda->map_x >= 0 && cub3d->map[(int)dda->map_y]
			&& cub3d->map[(int)dda->map_y][(int)dda->map_x] == '1')
			dda->hit = 1;
	}
}

/* Calcule la distance perpendiculaire au mur pour éviter l'effet fish-eye */
double	calc_perpendicular_wall_distance(t_dda *dda, double ray_dir_x,
	double ray_dir_y, t_cub3d *cub3d)
{
	double	perp_wall_dist;

	if (dda->side == 0)
	{
		perp_wall_dist = (dda->map_x - cub3d->player.pos_x
				+ (1 - dda->step_x) / 2) / ray_dir_x;
	}
	else
	{
		perp_wall_dist = (dda->map_y - cub3d->player.pos_y
				+ (1 - dda->step_y) / 2) / ray_dir_y;
	}
	return (ft_abs(perp_wall_dist));
}
