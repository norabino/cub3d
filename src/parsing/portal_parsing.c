/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ju <ju@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ju                #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ju               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	tp_already_set(t_cub3d *cub3d, char name)
{
	int	i;

	if (!cub3d || !cub3d->tp_portals || cub3d->nb_portals <= 0)
		return (0);
	i = 0;
	while (i < cub3d->nb_portals)
	{
		if (cub3d->tp_portals[i].name == name)
			return (1);
		i++;
	}
	return (0);
}

t_point	find_correspondance(t_cub3d *cub3d, int tmp_y, int tmp_x)
{
	int		y;
	int		x;

	y = 0;
	while (cub3d->map[y])
	{
		x = 0;
		while (cub3d->map[y][x])
		{
			if (cub3d->map[y][x] == cub3d->map[tmp_y][tmp_x]
				&& !(y == tmp_y && x == tmp_x))
				return ((t_point){x, y});
			x++;
		}
		y++;
	}
	return ((t_point){-1, -1});
}
