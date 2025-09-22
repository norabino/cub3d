/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:06:11 by gicomlan          #+#    #+#             */
/*   Updated: 2025/07/08 17:06:7 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	flood_fill_z(char ***map, t_point here, char to_fill)
{
	if (here.y < 0 || here.x < 0)
		return (1);
	if (!(*map)[here.y] || here.x >= ft_strlen((*map)[here.y]))
		return (1);
	if (!(*map)[here.y][here.x] || (*map)[here.y][here.x] != to_fill)
		return (1);
	(*map)[here.y][here.x] = 'Z';
	if (!flood_fill_z(map, (t_point){here.x - 1, here.y}, to_fill) ||
		!flood_fill_z(map, (t_point){here.x + 1, here.y}, to_fill) ||
		!flood_fill_z(map, (t_point){here.x, here.y - 1}, to_fill) ||
		!flood_fill_z(map, (t_point){here.x, here.y + 1}, to_fill))
		return (0);
	return (1);
}

int	flood_fill(char ***map, t_point here, char to_f, char new)
{
	if (here.y < 0 || here.x < 0)
		return (0);
	if (!(*map)[here.y] || here.x >= ft_strlen((*map)[here.y]))
		return (0);
	if (!(*map)[here.y][here.x])
		return (0);
	if ((*map)[here.y][here.x] != to_f
		|| (*map)[here.y][here.x] == '1'
		|| (*map)[here.y][here.x] == new)
		return (1);
	if (!check_adjacent(here.y, here.x, (*map), new))
		return (0);
	if (!in_map((*map)[here.y][here.x]))
		return (0);
	(*map)[here.y][here.x] = new;
	if (!flood_fill(map, (t_point){here.x - 1, here.y}, to_f, new)
		|| !flood_fill(map, (t_point){here.x + 1, here.y}, to_f, new)
		|| !flood_fill(map, (t_point){here.x, here.y - 1}, to_f, new)
		|| !flood_fill(map, (t_point){here.x, here.y + 1}, to_f, new))
		return (0);
	return (1);
}

int	check_adjacent(int y, int x, char **map, char new)
{
	if (x <= 0 || !map[y] || x >= ft_strlen(map[y]) - 1)
		return (0);
	if (y <= 0 || !map[y - 1] || !map[y + 1])
		return (0);
	if (x >= ft_strlen(map[y])
		|| (!in_map(map[y][x - 1]) && map[y][x - 1] != new))
		return (0);
	if (x + 1 >= ft_strlen(map[y])
		|| (!in_map(map[y][x + 1]) && map[y][x + 1] != new))
		return (0);
	if (x >= ft_strlen(map[y - 1])
		|| (!in_map(map[y - 1][x]) && map[y - 1][x] != new))
		return (0);
	if (x >= ft_strlen(map[y + 1])
		|| (!in_map(map[y + 1][x]) && map[y + 1][x] != new))
		return (0);
	return (1);
}

t_point	find_player_position(t_cub3d *cub3d, char **map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < ft_tablen(map) - 1)
	{
		x = 0;
		while (x < ft_strlen(map[y]) - 1)
		{
			if (is_letter(map[y][x]))
				return ((t_point){x, y});
			x++;
		}
		y++;
	}
	exit_error("Player position not found!", cub3d);
	return ((t_point){-1, -1});
}
