/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:48:42 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 12:222:02 by norabino         ###   ########.fr       */
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
		if (ft_is_letter(file[*idx][0]))
		{
			j = 0;
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
		exit_error("MIssing texture", textures->cubd);
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
				exit_error("Wrong ceiling color args", colors->cubd);
		}
	else if (c == 'F')
		while (split[++i])
		{
			colors->floor[i] = ft_atoi(split[i]);
			if (colors->floor[i] < 0
				|| colors->floor[i] > 255)
				exit_error("Wrong floor color args", colors->cubd);
		}
}

int	ft_check_colors(t_colors *colors, char **file, int *idx)
{
	int		j;
	char	**split;

	(*idx) = 0;
	while (file[*idx] && !all_colors_set(*colors))
	{
		if (file[*idx][0] == 'C' || file[*idx][0] == 'F')
		{
			j = 0;
			j += skip_letter(file[*idx][0], file[*idx][1]);
			skip_spaces(file[*idx], &j);
			split = ft_split(&file[*idx][j], ',');
			set_color(colors, split, file[*idx][0]);
		}
		(*idx)++;
	}
	if (!all_colors_set(*colors))
		exit_error("Wrong colors", colors->cubd);
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
			if (ft_is_letter(cub3d->map[y][x]))
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

void	check_zero_remaining(t_cub3d *cub3d, char **work_map)
{
	int	y;
	int	x;

	y = 0;
	while (work_map[y])
	{
		while (work_map[y][x])
		{
			y = 0;
			// a finir
		}
	}
}

int	ft_check_map_valid(t_cub3d *cub3d)
{
    char	**work_map;
    t_point	size;
	t_point	player_pos;

    ft_check_letter(cub3d);
    work_map = map_cpy(cub3d->map);
    size.y = 0;
    while (cub3d->map[size.y])
        size.y++;
    size.x = ft_get_max_width(cub3d->map);
    player_pos = find_player_position(cub3d, work_map, size);
	work_map[player_pos.y][player_pos.x] = '0';
    if (!flood_fill(work_map, size, player_pos))
    {
		free_map(work_map);
		exit_error("Map is not closed or touches invalid spaces!", cub3d);
	}
	if (!check_no_invalid_adjacent(work_map, size))
	{
		free_map(work_map);
		exit_error("Accessible area touches empty spaces!", cub3d);
	}
	check_zero_remaining(cub3d, work_map);
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
	return(1);
}
