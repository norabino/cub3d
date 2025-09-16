/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 10:39:05 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include <math.h>

double	calc_sprite_distance(t_cub3d *cub3d, double sprite_x, double sprite_y)
{
	double	dx;
	double	dy;

	dx = cub3d->player.pos_x - sprite_x;
	dy = cub3d->player.pos_y - sprite_y;
	return (dx * dx + dy * dy);
}

int	is_sprite_in_fov(t_cub3d *cub3d, double sprite_x, double sprite_y)
{
	double	dx;
	double	dy;
	double	cross_product;
	double	dot_product;
	double	sprite_angle;

	dx = sprite_x - cub3d->player.pos_x;
	dy = sprite_y - cub3d->player.pos_y;
	dot_product = dx * cub3d->player.dir_x + dy * cub3d->player.dir_y;
	if (dot_product <= 0)
		return (0);
	cross_product = dx * cub3d->player.dir_y - dy * cub3d->player.dir_x;
	sprite_angle = atan2(fabs(cross_product), dot_product);
	if (sprite_angle > M_PI / 3)
		return (0);
	return (1);
}

int	check_map_bounds(t_cub3d *cub3d, double x, double y)
{
	if (x < 0 || y < 0)
		return (1);
	if ((int)y >= ft_tablen(cub3d->map))
		return (1);
	if ((int)x >= (int)ft_strlen(cub3d->map[(int)y]))
		return (1);
	return (0);
}

int	is_wall_at_position(t_cub3d *cub3d, double x, double y)
{
	char	cell;

	cell = cub3d->map[(int)y][(int)x];
	if (cell == '1')
		return (1);
	return (0);
}
