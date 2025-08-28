/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_set_file_old.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:33:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/28 22:00:59 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_direction(t_cub3d *cub3d, char dir)
{
	if (dir == 'N')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = -1;
	}
	else if (dir == 'S')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = 1;
	}
	else if (dir == 'E')
	{
		cub3d->player.dir_x = 1;
		cub3d->player.dir_y = 0;
	}
	else if (dir == 'W')
	{
		cub3d->player.dir_x = -1;
		cub3d->player.dir_y = 0;
	}
}

int	tp_already_set(t_cub3d *cub3d, char name)
{
	int	i;

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
	char	name;
	int		x;
	int		y;

	name = cub3d->map[tmp_y][tmp_x];
	y = 0;
	while (cub3d->map[y])
	{
		x = 0;
		while (cub3d->map[y][x])
		{
			if (cub3d->map[y][x] == name && !(x == tmp_x && y == tmp_y))
				return ((t_point){x, y});
			x++;
		}
		y++;
	}
	return ((t_point){-1, -1});
}

t_prtl	find_a_portal(t_cub3d *cub3d, char **map)
{
	t_prtl	portal;
	int			y;
	int			x;

	portal = (t_prtl){0, {-1, -1}, {-1, -1}, {{0}, 0, 0, {100, 100, 100}, 0}};
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_lowercase(map[y][x]) && !tp_already_set(cub3d, map[y][x]))
			{
				portal.name = map[y][x];
				portal.p1.x = x;
				portal.p1.y = y;
				portal.p2 = find_correspondance(cub3d, y, x);
				return (portal);
			}
			x++;
		}
		y++;
	}
	return (portal);
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

int	check_and_set_file(t_cub3d *cub3d, char **file)
{
	int	idx_line;
	int	tmp;

	idx_line = 0;
	ft_check_textures(&cub3d->textures, file, &idx_line);
	tmp = idx_line;
	ft_check_colors(&cub3d->colors, file, &idx_line);
	if (tmp > idx_line)
		idx_line = tmp;
	ft_check_map(cub3d, file, &idx_line);
	ft_check_portals(cub3d);
	set_prtls(cub3d);
	set_direction(cub3d, cub3d->player.dir);
	cub3d->player.pos_x = (double)cub3d->player.pos_x + 0.5;
	cub3d->player.pos_y = (double)cub3d->player.pos_y + 0.5;
	cub3d->player.fov = 66;
	return (1);
}
