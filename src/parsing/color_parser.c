/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/17 17:56:06 by norabino         ###   ########.fr       */
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
static void	validate_no_color_duplicate(t_cub3d *cub3d, char c, int i)
{
	if (c == 'C' && cub3d->colors.ceiling[0] != -1)
	{
		cub3d->nb_error_line = i;
		exit_error("Duplicate ceiling color", cub3d);
	}
	if (c == 'F' && cub3d->colors.floor[0] != -1)
	{
		cub3d->nb_error_line = i;
		exit_error("Duplicate floor color", cub3d);
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
int	parse_color_line(t_cub3d *cub3d, char **file, int *idx, int i)
{
	int	j;
	int	z;

	j = 0;
	skip_spaces(file[i], &j);
	if ((file[i][j] == 'C' || file[i][j] == 'F'))
	{
		validate_no_color_duplicate(cub3d, file[i][j], j);
		z = j;
		parse_color_values(cub3d, file[i], j, z);
	}
	if ((*idx) == 0 && all_colors_set(cub3d))
		(*idx) = i + 1;
	return (1);
}
