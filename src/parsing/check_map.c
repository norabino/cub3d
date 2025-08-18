/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:33:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/18 15:30:08 by norabino         ###   ########.fr       */
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
	cub3d->player.posX = player_pos.x;
	cub3d->player.posY = player_pos.y;
	(*work_map)[player_pos.y][player_pos.x] = '0';
}

static int	process_flood(t_cub3d *cub3d, char **work_map, int *ff_count)
{
	t_point	*p;

	p = check_char_remaining(work_map, '0');
	if (p)
	{
		if (!flood_fill(&work_map, *p, '0', 'F'))
		{
			free_map(work_map);
			exit_error("map ouverte", cub3d);
		}
		(*ff_count)++;
		return (1);
	}
	return (0);
}

int	ft_check_map_valid(t_cub3d *cub3d)
{
	char	**work_map;
	int		nb_maps;
	int		nb_flood_fill;

	nb_flood_fill = 0;
	prepare_map(cub3d, &work_map);
	nb_maps = count_islands(cub3d, work_map);
	while (process_flood(cub3d, work_map, &nb_flood_fill))
		;
	if (nb_flood_fill != nb_maps)
	{
		free_map(work_map);
		exit_error("Map contains inaccessible areas", cub3d);
	}
	free_map(work_map);
	return (1);
}

int	ft_check_map(t_cub3d *cub3d, char **file, int *idx_line)
{
	int	begin;

	while (file[*idx_line] && !ft_strchr(file[*idx_line], '1'))
		(*idx_line)++;
	if (!file[*idx_line])
		exit_error("No map found", cub3d);
	begin = *idx_line;
	while (file[*idx_line])
		(*idx_line)++;
	cub3d->map = malloc(sizeof(char *) * (*idx_line) - begin + 2);
	(*idx_line) = 0;
	while (file[*idx_line + begin])
	{
		cub3d->map[*idx_line] = file[*idx_line + begin];
		(*idx_line)++;
	}
	cub3d->map[*idx_line] = NULL;
	ft_check_map_valid(cub3d);
	return (1);
}
