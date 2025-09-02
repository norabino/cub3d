/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:41:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/02 03:30:08 by jdupuis          ###   ########.fr       */
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
	printf("DEBUG: Checking portal correspondences...\n");
	while (i < 26)
	{
		if (cub3d->portals[i] > 0)
		{
			printf("DEBUG: Portal '%c' appears %d times\n", (char)('a' + i), cub3d->portals[i]);
			if (cub3d->portals[i] == 2)
				cpt++;
			else if (cub3d->portals[i] != 1)
				exit_error("No correspondance for portal(s)", cub3d);
		}
		i++;
	}
	printf("DEBUG: Found %d valid portal pairs\n", cpt);
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

char	safe_map_access(t_cub3d *cub3d, int y, int x)
{
	if (!cub3d || !cub3d->map)
		return ('1');
	if (y < 0 || x < 0)
		return ('1');
	if (!cub3d->map[y])
		return ('1');
	if (x >= (int)ft_strlen(cub3d->map[y]))
		return ('1');
	return (cub3d->map[y][x]);
}
