/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:33:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/05 02:52:14 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Prépare une copie de la carte pour les vérifications */
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

/* Teste si une zone de la carte est accessible avec flood fill */
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
			exit_error("map ouverte", cub3d);
		}
		free(p);
		return (1);
	}
	return (0);
}

/* Vérifie la validité des portails sur la carte */
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

/* Vérifie que toutes les zones de la carte sont bien fermées */
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

/* Extrait et stocke la carte depuis le fichier de configuration */
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
	cub3d->map = calloc((*idx_line) - begin + 2, sizeof(char *));
	if (!cub3d->map)
		exit_error("Failed to allocate memory for map", cub3d);
	(*idx_line) = 0;
	while (file[*idx_line + begin])
	{
		cub3d->map[*idx_line] = ft_strdup(file[*idx_line + begin]);
		if (!cub3d->map[*idx_line])
			exit_error("Failed to duplicate map line", cub3d);
		(*idx_line)++;
	}
	cub3d->map[*idx_line] = NULL;
	ft_check_map_valid(cub3d);
	return (1);
}
