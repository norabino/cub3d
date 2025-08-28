/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ju <ju@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ju                #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ju               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_prtl	create_empty_portal(void)
{
	t_prtl	portal;

	portal.name = '\0';
	portal.p1.x = -1;
	portal.p1.y = -1;
	portal.p2.x = -1;
	portal.p2.y = -1;
	return (portal);
}

static t_prtl	create_portal_from_position(t_cub3d *cub3d, char **map,
	int y, int x)
{
	t_prtl	portal;

	portal.name = map[y][x];
	portal.p1.x = x;
	portal.p1.y = y;
	portal.p2 = find_correspondance(cub3d, y, x);
	return (portal);
}

t_prtl	find_a_portal(t_cub3d *cub3d, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_lowercase(map[y][x]) && !tp_already_set(cub3d, map[y][x]))
				return (create_portal_from_position(cub3d, map, y, x));
			x++;
		}
		y++;
	}
	return (create_empty_portal());
}

void	set_prtls(t_cub3d *cub3d)
{
	int	i;

	cub3d->tp_portals = malloc(sizeof(t_prtl) * (cub3d->nb_portals + 1));
	i = 0;
	while (i < cub3d->nb_portals)
	{
		cub3d->tp_portals[i] = find_a_portal(cub3d, cub3d->map);
		i++;
	}
	cub3d->tp_portals[i] = (t_prtl){0, {-1, -1}, {-1, -1},
	{{0}, 0, 0, {100, 100, 100}, 0}};
}
