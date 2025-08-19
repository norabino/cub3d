/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/19 15:17:34 by norabino         ###   ########.fr       */
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

static void	verify_colors(t_colors *colors)
{
	if (colors->ceiling[0] == -1 || colors->ceiling[2] == -1)
		exit_error("Ceiling color is Missing", colors->cub3d);
	else if (colors->floor[0] == -1 || colors->floor[2] == -1)
		exit_error("Floor color is Missing", colors->cub3d);
}

int	ft_check_colors(t_colors *colors, char **file, int *idx)
{
	int		i;
	int		j;
	int		z;

	i = 0;
	(*idx) = 0;
	while (file[i])
	{
		j = 0;
		skip_spaces(file[i], &j);
		if ((file[i][j] == 'C' || file[i][j] == 'F'))
		{
			check_duplicate(colors, file[i][j]);
			z = j;
			process_color(colors, file[i], j, z);
		}
		if ((*idx) == 0 && all_colors_set(*colors))
			(*idx) = i + 1;
		i++;
	}
	verify_colors(colors);
	return (1);
}
