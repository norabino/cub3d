/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/17 22:35:50 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <string.h>

/* Assigne les valeurs de couleur selon le type (C ou F) */
void	assign_color_values(t_cub3d *cub3d, char **split, char c)
{
	if (c == 'C')
		set_ceiling(cub3d, split);
	else if (c == 'F')
		set_floor(cub3d, split);
}

/* Valide qu'il n'y a pas de couleur dupliquée */
static void	color_duplicate(t_cub3d *cub3d, char c, int i)
{
	if (c == 'C' && cub3d->colors.ceiling[0] != -1)
	{
		cub3d->nb_error_line = i;
		exit_error("Ceiling color duplicate", cub3d);
	}
	if (c == 'F' && cub3d->colors.floor[0] != -1)
	{
		cub3d->nb_error_line = i;
		exit_error("Floor color duplicate", cub3d);
	}
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
	if (!cub3d->textures.ceiling && cub3d->colors.ceiling[0] == -1)
		exit_error("Ceiling color is missing", cub3d);
	if (!cub3d->textures.floor && cub3d->colors.floor[0] == -1)
		exit_error("Floor color is missing", cub3d);
}

/* Parse une ligne de couleur et met à jour les structures */
int	parse_color_line(t_cub3d *cub3d, int i)
{
	int	j;
	int	z;

	j = 0;
	skip_spaces(cub3d->file[i], &j);
	if ((cub3d->file[i][j] == 'C' || cub3d->file[i][j] == 'F'))
	{
		if (strstr(cub3d->file[i], ".xpm"))
			return (-1);
		color_duplicate(cub3d, cub3d->file[i][j], j);
		z = j;
		parse_color_values(cub3d, cub3d->file[i], j, z);
	}
	return (i);
}
