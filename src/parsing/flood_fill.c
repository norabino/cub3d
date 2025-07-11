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

int	ft_get_max_width(char **map)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		current_width = ft_strlen(map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int	flood_fill_z(char ***map, t_point here, char to_fill)
{
	if (here.y < 0 || here.x < 0)
		return (1);
	if (!(*map)[here.y] || here.x >= ft_strlen((*map)[here.y]))
		return (1);
	if (!(*map)[here.y][here.x] || (*map)[here.y][here.x] != to_fill)
		return (1);
	(*map)[here.y][here.x] = 'Z';
	if (!flood_fill_z(map, (t_point){here.x - 1, here.y, 0, NULL}, to_fill) ||
		!flood_fill_z(map, (t_point){here.x + 1, here.y, 0, NULL}, to_fill) ||
		!flood_fill_z(map, (t_point){here.x, here.y - 1, 0, NULL}, to_fill) ||
		!flood_fill_z(map, (t_point){here.x, here.y + 1, 0, NULL}, to_fill))
		return (0);
	return (1);
}

int	flood_fill(char ***map, t_point here, char to_fill, char new)
{
	// Vérifier les bornes AVANT tout accès
	if (here.y < 0 || here.x < 0)
		return (0);
	if (!(*map)[here.y] || here.x >= ft_strlen((*map)[here.y]))
		return (0);
	if (!(*map)[here.y][here.x])
		return (0);
	if ((*map)[here.y][here.x] != to_fill
		|| (*map)[here.y][here.x] == '1'
		|| (*map)[here.y][here.x] == new)
		return (1);

	// Vérifier si on peut utiliser check_adjacent
	if (!check_adjacent(here.y, here.x, (*map), new))
		return (0);

	if (!in_map((*map)[here.y][here.x]))
		return (0);
	(*map)[here.y][here.x] = new;
	if (!flood_fill(map, (t_point){here.x - 1, here.y, 0, NULL}, to_fill, new) ||
		!flood_fill(map, (t_point){here.x + 1, here.y, 0, NULL}, to_fill, new) ||
		!flood_fill(map, (t_point){here.x, here.y - 1, 0, NULL}, to_fill, new) ||
		!flood_fill(map, (t_point){here.x, here.y + 1, 0, NULL}, to_fill, new))
		return (0);
	return (1);
}

int	check_adjacent(int y, int x, char **map, char new)
{
	// Vérifier les bornes avant chaque accès
	if (x <= 0 || !map[y] || x >= ft_strlen(map[y]) - 1)
		return (0);
	if (y <= 0 || !map[y - 1] || !map[y + 1])
		return (0);

	// Maintenant on peut accéder en sécurité
	if ((!map[y][x - 1] || !in_map(map[y][x - 1])) && map[y][x - 1] != new)
		return (0);
	if ((!map[y][x + 1] || !in_map(map[y][x + 1])) && map[y][x + 1] != new)
		return (0);
	if ((!map[y - 1][x] || !in_map(map[y - 1][x])) && map[y - 1][x] != new)
		return (0);
	if ((!map[y + 1][x] || !in_map(map[y + 1][x])) && map[y + 1][x] != new)
		return (0);
	return (1);
}

// Verif qu'aucune case accessible par le joueur ne touche un char invalide
/*int	check_no_invalid_adjacent(char **map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < collen(map, y, x))
	{
		x = 0;
		while (x < linelen(map, y, x))
		{
			if (map[y][x] == 'F')
			{
				if (!check_adjacent(y, x, map))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}*/

t_point find_player_position(t_cub3d *cub3d, char **map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	//printf("{%d, %d} ; linelen = %d ; collen = %d", y, x, ft_tablen(map) - 1, ft_strlen(map[y]) - 1);
	while (y < ft_tablen(map) - 1)
	{
		x = 0;
		while (x < ft_strlen(map[y]) - 1)
		{
			if (is_letter(map[y][x]))
				return ((t_point){x, y, map[y][x], cub3d});
			x++;
		}
		y++;
	}
	exit_error("Player position not found!", cub3d);
	return ((t_point){-1, -1, 0, cub3d});
}

// int	ft_check_islands(char **work_map, t_cub3d *cub3d, int nb_islands)
// {
// 	t_point	*point;
// 	int	i;
// 	int	j;
// 	int	cpt;

// 	i = 0;
// 	cpt = 0;
// 	while (cpt < nb_islands)
// 	{
// 		point = check_zero_remaining(cub3d, work_map);
// 		if (point == NULL)
// 			break;
// 		if (!flood_fill(&work_map, NULL, *point, cub3d->alpha[cpt]))
// 			exit_error("non", cub3d);


// 	}
// }
//boucle i < nb_island
	//{
	//		fonction qui cherche le premier 0
	//		flood_fill avec le char 93 + i
	//		check_island aux coordonnée de lancement du flood_fill avec le char du flood_fill
	//		i++;
	//}