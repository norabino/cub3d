/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:33:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/22 18:53:53 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	prepare_map(t_cub3d *cub3d, char ***work_map)
{
	t_point	player_pos;

	ft_check_letter(cub3d);
	*work_map = map_cpy(cub3d->map);
	player_pos = find_player_position(cub3d, *work_map);
	cub3d->player.dir = (*work_map)[player_pos.y][player_pos.x];
	cub3d->player.pos_x = player_pos.x;
	cub3d->player.pos_y = player_pos.y;
	(*work_map)[player_pos.y][player_pos.x] = '0';
	replace_portals_by_zero(work_map);
}

static int	process_flood(t_cub3d *cub3d, char **work_map)
{
	t_point	*p;

	p = check_char_remaining(work_map, '0');
	if (p)
	{
		if (!flood_fill(&work_map, *p, '0', 'F'))
		{
			free(p);
			free_map(work_map);
			exit_error("Open map", cub3d);
		}
		free(p);
		return (1);
	}
	return (0);
}

void	ft_check_portals(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (cub3d->map[y])
	{
		x = 0;
		while (cub3d->map[y][x])
		{
			if (is_lowercase(cub3d->map[y][x]))
			{
				cub3d->portals[cub3d->map[y][x] - 97]++;
				if (cub3d->portals[cub3d->map[y][x] - 97] > 2)
					exit_error("More than two entry/exit for portal(s)", cub3d);
			}
			x++;
		}
		y++;
	}
	check_correspondance(cub3d);
}

int	ft_check_map_valid(t_cub3d *cub3d)
{
	char	**work_map;
	int		nb_maps;
	int		nb_flood_fill;

	nb_flood_fill = 0;
	prepare_map(cub3d, &work_map);
	nb_maps = count_islands(cub3d, work_map);
	while (process_flood(cub3d, work_map))
		nb_flood_fill++;
	if (nb_flood_fill != nb_maps)
	{
		free_map(work_map);
		exit_error("Map contains inaccessible areas", cub3d);
	}
	free_map(work_map);
	return (1);
}

int	ft_check_map(t_cub3d *cub3d, int *idx_line)
{
	int	begin;

	while (cub3d->file[*idx_line] && !ft_strchr(cub3d->file[*idx_line], '1'))
		(*idx_line)++;
	if (!cub3d->file[*idx_line])
		exit_error("No map found", cub3d);
	begin = *idx_line;
	while (cub3d->file[*idx_line])
		(*idx_line)++;
	cub3d->map = ft_calloc((*idx_line) - begin + 2, sizeof(char *));
	(*idx_line) = 0;
	while (cub3d->file[*idx_line + begin])
	{
		cub3d->map[*idx_line] = ft_strdup(cub3d->file[*idx_line + begin]);
		(*idx_line)++;
	}
	cub3d->map[*idx_line] = NULL;
	ft_check_map_valid(cub3d);
	return (1);
}
