/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:07:42 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/02 03:25:28 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_adjacent_zeros(char **map, int y, int x)
{
	if (map[y] && map[y][x + 1] && map[y][x + 1] == '0')
		return (1);
	else if (x != 0 && map[y] && map[y][x - 1] == '0')
		return (1);
	else if (map[y + 1] && map[y + 1][x] && map[y + 1][x] == '0')
		return (1);
	else if (y != 0 && map[y - 1] && map[y - 1][x] && map[y - 1][x] == '0')
		return (1);
	return (0);
}

t_point	*check_char_remaining(char **work_map, char c)
{
	int		y;
	int		x;
	t_point	*p;

	p = malloc(sizeof(t_point));
	if (!p)
		return (NULL);
	y = 0;
	while (work_map[y])
	{
		x = 0;
		while (work_map[y][x])
		{
			if (work_map[y][x] == c)
			{
				p->y = y;
				p->x = x;
				return (p);
			}
			x++;
		}
		y++;
	}
	free(p);
	return (NULL);
}

void	normalize_map(char **trash)
{
	t_point	*p;

	p = check_char_remaining(trash, '1');
	while (p && check_adjacent_zeros(trash, p->y, p->x))
	{
		trash[p->y][p->x] = '2';
		free(p);
		p = check_char_remaining(trash, '1');
	}
	if (p)
		free(p);
	p = check_char_remaining(trash, '0');
	while (p)
	{
		trash[p->y][p->x] = '2';
		free(p);
		p = check_char_remaining(trash, '0');
	}
	if (p)
		free(p);
}

int	count_islands(t_cub3d *cub3d, char **work_map)
{
	int		nb_islands;
	char	**trash;
	t_point	*p;

	(void)cub3d;
	trash = map_cpy(work_map);
	normalize_map(trash);
	nb_islands = 0;
	p = check_char_remaining(trash, '2');
	while (p)
	{
		if (!flood_fill_z(&trash, *p, '2'))
		{
			free(p);
			free_map(trash);
			exit_error("map error 1", cub3d);
		}
		nb_islands++;
		free(p);
		p = check_char_remaining(trash, '2');
	}
	free_map(trash);
	return (nb_islands);
}

double	ft_abs(double nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}
