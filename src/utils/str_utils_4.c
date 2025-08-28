/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:41:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/28 20:40:41 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_lowercase(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

void	check_correspondance(t_cub3d *cub3d)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (i < 26)
	{
		if (cub3d->portals[i] > 0)
		{
			if (cub3d->portals[i] == 2)
				cpt++;
			else if (cub3d->portals[i] != 1)
				exit_error("No correspondance for portal(s)", cub3d);
		}
		i++;
	}
	cub3d->nb_portals = cpt;
}

void	replace_portals_by_zero(char ***map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while ((*map)[y])
	{
		x = 0;
		while ((*map)[y][x])
		{
			if (is_lowercase((*map)[y][x]))
				(*map)[y][x] = '0';
			x++;
		}
		y++;
	}
}
