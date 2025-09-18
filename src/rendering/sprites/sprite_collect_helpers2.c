/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect_helpers2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:46:46 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 19:21:10 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	check_raycast_bounds(t_cub3d *cub3d, double current_x,
	double current_y)
{
	if (current_x < 0 || current_y < 0)
		return (1);
	if ((int)current_y >= ft_tablen(cub3d->map))
		return (1);
	if ((int)current_x >= (int)ft_strlen(cub3d->map[(int)current_y]))
		return (1);
	return (0);
}

static int	check_raycast_collision(t_cub3d *cub3d, double current_x,
	double current_y, int *hit_portal)
{
	char	cell;

	cell = cub3d->map[(int)current_y][(int)current_x];
	if (cell == '1')
	{
		if (!*hit_portal)
			return (1);
		else
			return (1);
	}
	if (cell >= 'A' && cell <= 'Z')
		*hit_portal = 1;
	return (0);
}

static void	init_raycast_data(t_cub3d *cub3d, double sprite_x, double sprite_y,
	double *raycast_data)
{
	raycast_data[0] = sprite_x - cub3d->player.pos_x;
	raycast_data[1] = sprite_y - cub3d->player.pos_y;
	raycast_data[2] = sqrt(raycast_data[0] * raycast_data[0]
			+ raycast_data[1] * raycast_data[1]);
	raycast_data[5] = cub3d->player.pos_x;
	raycast_data[2] = cub3d->player.pos_y;
}

static int	perform_raycast_check(t_cub3d *cub3d, double *raycast_data,
	int steps)
{
	int	i;
	int	hit_portal;

	hit_portal = 0;
	i = 1;
	while (i < steps - 1)
	{
		raycast_data[5] += raycast_data[3];
		raycast_data[2] += raycast_data[4];
		if (check_raycast_bounds(cub3d, raycast_data[5], raycast_data[2]))
			return (1);
		if (check_raycast_collision(cub3d, raycast_data[5], raycast_data[2],
				&hit_portal))
			return (1);
		i++;
	}
	return (0);
}

int	is_sprite_hidden(t_cub3d *cub3d, double sprite_x, double sprite_y)
{
	double	raycast_data[6];
	int		steps;

	init_raycast_data(cub3d, sprite_x, sprite_y, raycast_data);
	if (raycast_data[2] < 0.5)
		return (0);
	steps = (int)(raycast_data[2] * 4);
	if (steps < 20)
		steps = 20;
	if (steps > 200)
		steps = 200;
	raycast_data[3] = raycast_data[0] / steps;
	raycast_data[4] = raycast_data[1] / steps;
	return (perform_raycast_check(cub3d, raycast_data, steps));
}
