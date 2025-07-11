/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_set_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:33:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/11 14:46:19 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	all_colors_set(t_colors colors)
{
	if (colors.ceiling[0] == -1 || colors.ceiling[1] == -1 || colors.ceiling[1] == -1)
		return (0);
	if (colors.floor[0] == -1 || colors.floor[1] == -1 || colors.floor[1] == -1)
		return (0);
	return (1);
}

int	all_text_set(t_textures textures)
{
	if (!textures.north || !textures.south || !textures.west || !textures.east)
		return (0);
	return (1);
}
int	ft_check_textures(t_textures *textures, char **file, int *idx)
{
	int	j;

	*(idx) = 0;
	while (file[*idx] && !all_text_set(*textures))
	{
		j = 0;
		skip_spaces(file[*idx], &j);
		if (is_letter(file[*idx][j]))
		{
			j += skip_letter(file[*idx][0], file[*idx][1]);
			skip_spaces(file[*idx], &j);
			if (file[*idx][0] == 'N')
				textures->north = ft_substr(file[*idx], j, ft_strlen(file[*idx]) - j, 0);
			else if (file[*idx][0] == 'S')
				textures->south = ft_substr(file[*idx], j, ft_strlen(file[*idx]) - j, 0);
			else if (file[*idx][0] == 'W')
				textures->west = ft_substr(file[*idx], j, ft_strlen(file[*idx]) - j, 0);
			else if (file[*idx][0] == 'E')
				textures->east = ft_substr(file[*idx], j, ft_strlen(file[*idx]) - j, 0);
		}
		(*idx)++;
	}
	if (!all_text_set(*textures))
		exit_error("MIssing texture", textures->cub3d);
	return (1);
}

void	set_color(t_colors *colors, char **split, char c)
{
	int		i;

	i = -1;
	if (c == 'C')
		while (split[++i])
		{
			colors->ceiling[i] = ft_atoi(split[i]);
			if (colors->ceiling[i] < 0
				|| colors->ceiling[i] > 255)
				exit_error("Wrong ceiling color args", colors->cub3d);
		}
	else if (c == 'F')
		while (split[++i])
		{
			colors->floor[i] = ft_atoi(split[i]);
			if (colors->floor[i] < 0
				|| colors->floor[i] > 255)
				exit_error("Wrong floor color args", colors->cub3d);
		}
}

int	ft_check_colors(t_colors *colors, char **file, int *idx)
{
	int		j;
	char	**split;

	(*idx) = 0;
	while (file[*idx] && !all_colors_set(*colors))
	{
		j = 0;
		skip_spaces(file[*idx], &j);
		if (file[*idx][0] == 'C' || file[*idx][0] == 'F')
		{
			j += skip_letter(file[*idx][0], file[*idx][1]);
			skip_spaces(file[*idx], &j);
			split = ft_split(&file[*idx][j], ',');
			set_color(colors, split, file[*idx][0]);
		}
		(*idx)++;
	}
	if (!all_colors_set(*colors))
		exit_error("Wrong colors", colors->cub3d);
	return (1);
}

void	ft_check_letter(t_cub3d *cub3d)
{
	int	y;
	int	x;
	int	nb_spawn;

	y = 0;
	nb_spawn = 0;
	while (cub3d->map[y])
	{
		x = 0;
		while (cub3d->map[y][x])
		{
			if (is_letter(cub3d->map[y][x]))
				nb_spawn++;
			x++;
		}
		y++;
	}
	if (nb_spawn < 1)
		exit_error("No spawn in map !!\nMust be one.", cub3d);
	if (nb_spawn > 1)
		exit_error("Multiple spawn in map !!\nMust be one.", cub3d);
}

t_point	*check_char_remaining(t_cub3d *cub3d, char **work_map, char c)
{
	int		y;
	int		x;
	t_point	*p;

	p = malloc(sizeof(t_point *));
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
				p->direction = 0;
				p->cub3d = cub3d;
				return (p);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

int	check_adjacent_zeros(char **map, int y, int x)
{
	if (map[y][x + 1] == '0')
		return (1);
	else if (map[y][x - 1] == '0')
		return (1);
	else if (map[y + 1][x] == '0')
		return (1);
	else if (map[y - 1][x] == '0')
		return (1);
	return (0);
}

void normalize_map(t_cub3d *cub3d, char **trash)
{
	t_point	*p;

	p = check_char_remaining(cub3d, trash, '1');
	while (p && check_adjacent_zeros(trash, p->y, p->x))
	{
		trash[p->y][p->x] = '2';
		p = check_char_remaining(cub3d, trash, '1');
	}
	p = check_char_remaining(cub3d, trash, '0');
	while (p)
	{
		trash[p->y][p->x] = '2';
		p = check_char_remaining(cub3d, trash, '0');
	}
}

int	count_islands(t_cub3d *cub3d, char **work_map)
{
	int		nb_islands;
	char	**trash;
	t_point	*p;

	(void)cub3d;
	trash = map_cpy(work_map);
	normalize_map(cub3d, trash);
	nb_islands = 0;
	p = check_char_remaining(cub3d, trash, '2');
	while (p)
	{
		if (!flood_fill_z(&trash, *p, '2'))
		{
			free_map(trash);
			exit_error("map error 1", cub3d);
		}
		nb_islands++;
		p = check_char_remaining(cub3d, trash, '2');
	}
	free_map(trash);
	return (nb_islands);
}

int	ft_check_map_valid(t_cub3d *cub3d)
{
	char	**work_map;
	int		nb_maps;
	int		nb_flood_fill;
	t_point	player_pos;
	t_point	*p;

	nb_flood_fill = 0;
	ft_check_letter(cub3d);
	work_map = map_cpy(cub3d->map);
	player_pos = find_player_position(cub3d, work_map);
	work_map[player_pos.y][player_pos.x] = '0';
	//compter le nombre island
	nb_maps = count_islands(cub3d, work_map);
	p = check_char_remaining(cub3d, work_map, '0');
	while (p)
	{
		if (!flood_fill(&work_map, *p, '0', 'F'))
		{
			free_map(work_map);
			exit_error("map ouverte", cub3d);
		}
		nb_flood_fill++;
		p = check_char_remaining(cub3d, work_map, '0');
	}
	/*if (!check_no_invalid_adjacent(work_map))
	{
		free_map(work_map);
		exit_error("Accessible area touches empty spaces!", cub3d);
		}*/
	print_map(cub3d, cub3d->map);
	printf("\n\n");
	print_map(cub3d, work_map);
	printf("\nnb_flood_fill = %d\nnb_maps = %d", nb_flood_fill, nb_maps);
	if (nb_flood_fill != nb_maps)
		exit_error("Map contains inaccessible areas", cub3d);
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
	return (1);
}
