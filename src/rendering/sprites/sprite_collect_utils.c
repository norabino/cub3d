/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:46:46 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/22 19:19:46 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	should_display_sprite(t_cub3d *cub3d, double sprite_x, double sprite_y)
{
	double	distance;

	distance = calc_sprite_distance(cub3d, sprite_x, sprite_y);
	if (distance > MAX_SPRITE_DISTANCE * MAX_SPRITE_DISTANCE)
		return (1);
	if (!is_sprite_in_fov(cub3d, sprite_x, sprite_y))
		return (1);
	if (is_sprite_hidden(cub3d, sprite_x, sprite_y))
		return (1);
	return (0);
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

	if (check_map_bounds(cub3d, x, y))
		return (1);
	cell = safe_map_access(cub3d, (int)y, (int)x);
	return (cell == '1');
}

void	calc_sprite_properties(t_cub3d *cub3d, t_sprite *sprite,
	t_sprite_calc *calc)
{
	calc->sprite_x = sprite->x - cub3d->player.pos_x;
	calc->sprite_y = sprite->y - cub3d->player.pos_y;
	calc->inv_det = 1.0 / (cub3d->view.plane_x * cub3d->player.dir_y
			- cub3d->player.dir_x * cub3d->view.plane_y);
	calc->transform_x = calc->inv_det * (cub3d->player.dir_y * calc->sprite_x
			- cub3d->player.dir_x * calc->sprite_y);
	calc->transform_y = calc->inv_det * (-cub3d->view.plane_y * calc->sprite_x
			+ cub3d->view.plane_x * calc->sprite_y);
	calc->sprite_screen_x = (int)((SCREEN_WIDTH / 2)
			* (1 + calc->transform_x / calc->transform_y));
	calc->sprite_height = ft_abs((int)(SCREEN_HEIGHT / calc->transform_y));
	calc->sprite_width = calc->sprite_height;
}

void	calc_sprite_screen_bounds(t_sprite_calc *calc)
{
	calc->draw_start_y = -calc->sprite_height / 2 + SCREEN_HEIGHT / 2;
	if (calc->draw_start_y < 0)
		calc->draw_start_y = 0;
	calc->draw_end_y = calc->sprite_height / 2 + SCREEN_HEIGHT / 2;
	if (calc->draw_end_y >= SCREEN_HEIGHT)
		calc->draw_end_y = SCREEN_HEIGHT - 1;
	calc->draw_start_x = -calc->sprite_width / 2 + calc->sprite_screen_x;
	calc->draw_end_x = calc->sprite_width / 2 + calc->sprite_screen_x;
	if (calc->draw_start_x < 0)
		calc->draw_start_x = 0;
	if (calc->draw_end_x >= SCREEN_WIDTH)
		calc->draw_end_x = SCREEN_WIDTH - 1;
}
