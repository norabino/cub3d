/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/01 21:19:34 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_all_colors(t_colors *colors, char **file, int *idx)
{
	int	i;

	i = 0;
	(*idx) = 0;
	while (file[i])
	{
		parse_color_line(colors, file[i], idx, i);
		i++;
	}
	validate_colors_complete(colors);
	return (1);
}

int	all_colors_set(t_colors colors)
{
	int	ceiling_complete;
	int	floor_complete;

	ceiling_complete = (colors.cub3d->textures.ceiling != NULL)
		|| (colors.ceiling[0] != -1 && colors.ceiling[1] != -1
			&& colors.ceiling[2] != -1);
	floor_complete = (colors.cub3d->textures.floor != NULL)
		|| (colors.floor[0] != -1 && colors.floor[1] != -1
			&& colors.floor[2] != -1);
	return (ceiling_complete && floor_complete);
}

void	set_ceiling(t_colors *colors, char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (i >= 3)
			exit_error("Invalid RGB ceiling nbs, must be 3", colors->cub3d);
		colors->ceiling[i] = ft_atoi(split[i]);
		if (colors->ceiling[i] < 0 || colors->ceiling[i] > 255)
			exit_error("Wrong ceiling color args [0-255]", colors->cub3d);
	}
}

void	set_floor(t_colors *colors, char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (i >= 3)
			exit_error("Invalid RGB floor nbs, must be 3", colors->cub3d);
		colors->floor[i] = ft_atoi(split[i]);
		if (colors->floor[i] < 0 || colors->floor[i] > 255)
			exit_error("Wrong floor color args [0-255]", colors->cub3d);
	}
}
