/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:30:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/25 14:49:31 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_corner_positions(t_cub3d *cub3d, double x, double y)
{
	if (cub3d->map[(int)(y - COLLISION_MARGIN)] == NULL ||
		cub3d->map[(int)(y - COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)]
		== '\0' ||
		cub3d->map[(int)(y - COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)]
		== '1')
		return (0);
	if (cub3d->map[(int)(y - COLLISION_MARGIN)] == NULL ||
		cub3d->map[(int)(y - COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)]
		== '\0' ||
		cub3d->map[(int)(y - COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)]
		== '1')
		return (0);
	return (1);
}

int	check_bottom_corners(t_cub3d *cub3d, double x, double y)
{
	if (cub3d->map[(int)(y + COLLISION_MARGIN)] == NULL ||
		cub3d->map[(int)(y + COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)]
		== '\0' ||
		cub3d->map[(int)(y + COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)]
		== '1')
		return (0);
	if (cub3d->map[(int)(y + COLLISION_MARGIN)] == NULL ||
		cub3d->map[(int)(y + COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)]
		== '\0' ||
		cub3d->map[(int)(y + COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)]
		== '1')
		return (0);
	return (1);
}
