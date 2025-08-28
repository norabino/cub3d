/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:20:24 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/28 20:26:46 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	is_portal(t_cub3d *cub3d)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)cub3d->player.pos_x;
	pos_y = (int)cub3d->player.pos_y;
	if (is_lowercase(cub3d->map[pos_y][pos_x]))
		return (cub3d->map[pos_y][pos_x]);
	return (0);
}

void	teleportation(t_cub3d *cub3d, t_portal portal)
{
	t_point	new;

	new = portal.p2;
	cub3d->player.pos_x = new.x;
	cub3d->player.pos_y = new.y;
}
