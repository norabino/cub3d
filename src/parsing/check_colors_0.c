/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/01 21:01:40 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_color(t_colors *colors, char **split, char c)
{
	if (c == 'C')
		set_ceiling(colors, split);
	else if (c == 'F')
		set_floor(colors, split);
}

static void	check_duplicate(t_colors *colors, char c)
{
	if (c == 'C' && colors->ceiling[0] != -1)
		exit_error("Duplicate ceiling color", colors->cub3d);
	if (c == 'F' && colors->floor[0] != -1)
		exit_error("Duplicate floor color", colors->cub3d);
}

static void	process_color(t_colors *colors, char *line, int j, int z)
{
	char	**split;

	j += skip_letter(line[z], line[j + 1]);
	skip_spaces(line, &j);
	split = ft_split(&line[j], ',');
	set_color(colors, split, line[z]);
	free_map(split);
}

void	verify_colors(t_colors *colors)
{
	int	ceiling_texture_exists;
	int	floor_texture_exists;

	ceiling_texture_exists = (colors->cub3d->textures.ceiling != NULL);
	floor_texture_exists = (colors->cub3d->textures.floor != NULL);
	if (!ceiling_texture_exists && (colors->ceiling[0] == -1
			|| colors->ceiling[2] == -1))
		exit_error("Ceiling color is Missing", colors->cub3d);
	if (!floor_texture_exists && (colors->floor[0] == -1
			|| colors->floor[2] == -1))
		exit_error("Floor color is Missing", colors->cub3d);
}

int	process_color_line(t_colors *colors, char *line, int *idx, int i)
{
	int	j;
	int	z;

	j = 0;
	skip_spaces(line, &j);
	if ((line[j] == 'C' || line[j] == 'F'))
	{
		if (ft_strrchr(line, '.') && ft_strrchr(line, '.')[1] == 'x'
			&& ft_strrchr(line, '.')[2] == 'p'
			&& ft_strrchr(line, '.')[3] == 'm')
			return (0);
		check_duplicate(colors, line[j]);
		z = j;
		process_color(colors, line, j, z);
	}
	if ((*idx) == 0 && all_colors_set(*colors))
		(*idx) = i + 1;
	return (1);
}
