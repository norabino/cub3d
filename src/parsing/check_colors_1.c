/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/19 21:50:53 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	all_colors_set(t_colors colors)
{
	if (colors.ceiling[0] == -1
		|| colors.ceiling[1] == -1
		|| colors.ceiling[1] == -1)
		return (0);
	if (colors.floor[0] == -1 || colors.floor[1] == -1 || colors.floor[1] == -1)
		return (0);
	return (1);
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
