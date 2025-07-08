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
				textures->north = ft_substr(file[*idx], j, ft_strlen(file[*idx]) - j);
			else if (file[*idx][0] == 'S')
				textures->south = ft_substr(file[*idx], j, ft_strlen(file[*idx]) - j);
			else if (file[*idx][0] == 'W')
				textures->west = ft_substr(file[*idx], j, ft_strlen(file[*idx]) - j);
			else if (file[*idx][0] == 'E')
				textures->east = ft_substr(file[*idx], j, ft_strlen(file[*idx]) - j);
		}
		(*idx)++;
	}
	if (!all_text_set(*textures))
		exit_error("MIssing texture");
	return (1);
}

void	set_color(t_colors *colors, char **split, char c)
{
	int		i;

	i = -1;
	if (c == 'C')
		while (split[++i])
			colors->ceiling[i] = ft_atoi(split[i]);
	else if (c == 'F')
		while (split[++i])
			colors->floor[i] = ft_atoi(split[i]);
}

int	ft_check_colors(t_colors *colors, char **file, int *idx)
{
	int		j;
	char	**split;

	(*idx) = 0;
	while (file[*idx])
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
	if (colors->ceiling[0] == -1 || colors->ceiling[1] == -1 || colors->ceiling[1] == -1)
		exit_error("Wrong ceiling colors");
	if (colors->floor[0] == -1 || colors->floor[1] == -1 || colors->floor[1] == -1)
		exit_error("Wrong floor colors");
	return (1);
}

void	ft_check_letter(char **map)
{
	int	i;
	int	j;
	int	nb_spawn;
	
	i = 0;
	nb_spawn = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_is_letter(map[i][j]))
				nb_spawn++;
			j++;
		}
		i++;
	}
	if (nb_spawn < 1)
		exit_error("No spawn in map !!\nMust be one.");
	if (nb_spawn > 1)
		exit_error("Multiple spawn in map !!\nMust be one.");
}

int	ft_check_map_valid(char **map)
{
    char	**work_map;
    t_point	size;
	t_point	player_pos;
    
    ft_check_letter(map);
    work_map = map_cpy(map);
    size.y = 0;
    while (map[size.y])
        size.y++;
    size.x = get_max_width(map); // Utiliser la largeur maximale
    // Trouver la position du joueur
    player_pos = find_player_position(work_map, size);
    if (player_pos.x == -1)
        exit_error("Player position not found!");
    // Effectuer le flood fill
    if (!flood_fill(work_map, size, player_pos))
    {
		free_map(work_map);
        exit_error("Map is not closed or touches invalid spaces!");
    }
    // Vérifier qu'aucun F ne touche un espace
    if (!check_no_space_adjacent(work_map, size))
    {
        free_map(work_map);
        exit_error("Accessible area touches empty spaces!");
    }
    free_map(work_map);
    return (1);
}

int	ft_check_map(char ***map, char **file, int *i)
{
	
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
	ft_check_map(&cub3d->map, file, &idx_line);
	return(1);
}
