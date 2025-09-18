/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:46:46 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 19:15:29 by jdupuis          ###   ########.fr       */
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
