/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:41:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/28 20:08:11 by jdupuis          ###   ########.fr       */
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
	while (cub3d->portals[i])
	{
		if (cub3d->portals[i] == 2 || is_lowercase(cub3d->portals[i]))
		{
			if (!is_lowercase(cub3d->portals[i]))
				cpt++;
			i++;
		}
		else
			exit_error("No correspondance for portal(s)", cub3d);
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
