/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/09 22:28:07 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Assigne les valeurs de couleur selon le type (C ou F) */
void	assign_color_values(t_cub3d *cub3d, char **split, char c)
{
	if (c == 'C')
		set_ceiling(cub3d, split);
	else if (c == 'F')
		set_floor(cub3d, split);
}

/* Valide qu'il n'y a pas de couleur dupliquée */
static void	validate_no_color_duplicate(t_cub3d *cub3d, char c)
{
	if (c == 'C' && cub3d->colors.ceiling[0] != -1)
		exit_error("Duplicate ceiling color", cub3d);
	if (c == 'F' && cub3d->colors.floor[0] != -1)
		exit_error("Duplicate floor color", cub3d);
}

/* Parse et valide les valeurs de couleur depuis une ligne */
static void	parse_color_values(t_cub3d *cub3d, char *line, int j, int z)
{
	char	**split;

	j += skip_letter(line[z], line[j + 1]);
	skip_spaces(line, &j);
	split = ft_split(&line[j], ',');
	assign_color_values(cub3d, split, line[z]);
	free_map(split);
}

/* Valide que toutes les couleurs nécessaires sont définies */
void	validate_colors_complete(t_cub3d *cub3d)
{
	int	ceiling_texture_exists;
	int	floor_texture_exists;

	ceiling_texture_exists = (cub3d->textures.ceiling != NULL);
	floor_texture_exists = (cub3d->textures.floor != NULL);
	if (!ceiling_texture_exists && (cub3d->colors.ceiling[0] == -1
			|| cub3d->colors.ceiling[2] == -1))
		exit_error("Ceiling color is Missing", cub3d);
	if (!floor_texture_exists && (cub3d->colors.floor[0] == -1
			|| cub3d->colors.floor[2] == -1))
		exit_error("Floor color is Missing", cub3d);
}

/* Parse une ligne de couleur et met à jour les structures */
int	parse_color_line(t_cub3d *cub3d, char *line, int *idx, int i)
{
	int	j;
	int	z;

	j = 0;
	skip_spaces(line, &j);
	if ((line[j] == 'C' || line[j] == 'F'))
	{
		if (check_extension(cub3d, line, ".xpm"))
			return (0);
		validate_no_color_duplicate(cub3d, line[j]);
		z = j;
		parse_color_values(cub3d, line, j, z);
	}
	if ((*idx) == 0 && all_colors_set(cub3d))
		(*idx) = i + 1;
	return (1);
}
