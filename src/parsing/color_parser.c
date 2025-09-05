/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/05 01:35:20 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Assigne les valeurs de couleur selon le type (C ou F) */
void	assign_color_values(t_colors *colors, char **split, char c)
{
	if (c == 'C')
		set_ceiling(colors, split);
	else if (c == 'F')
		set_floor(colors, split);
}

/* Valide qu'il n'y a pas de couleur dupliquée */
static void	validate_no_color_duplicate(t_colors *colors, char c)
{
	if (c == 'C' && colors->ceiling[0] != -1)
		exit_error("Duplicate ceiling color", colors->cub3d);
	if (c == 'F' && colors->floor[0] != -1)
		exit_error("Duplicate floor color", colors->cub3d);
}

/* Parse et valide les valeurs de couleur depuis une ligne */
static void	parse_color_values(t_colors *colors, char *line, int j, int z)
{
	char	**split;

	j += skip_letter(line[z], line[j + 1]);
	skip_spaces(line, &j);
	split = ft_split(&line[j], ',');
	assign_color_values(colors, split, line[z]);
	free_map(split);
}

/* Valide que toutes les couleurs nécessaires sont définies */
void	validate_colors_complete(t_colors *colors)
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

/* Parse une ligne de couleur et met à jour les structures */
int	parse_color_line(t_colors *colors, char *line, int *idx, int i)
{
	int	j;
	int	z;

	j = 0;
	skip_spaces(line, &j);
	if ((line[j] == 'C' || line[j] == 'F'))
	{
		if (check_extension(colors->cub3d, line, ".xpm"))
			return (0);
		validate_no_color_duplicate(colors, line[j]);
		z = j;
		parse_color_values(colors, line, j, z);
	}
	if ((*idx) == 0 && all_colors_set(*colors))
		(*idx) = i + 1;
	return (1);
}
