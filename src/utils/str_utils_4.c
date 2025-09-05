/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:41:35 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/05 01:35:20 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Vérifie si un caractère est une lettre minuscule */
int	is_lowercase(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

/* Vérifie que chaque portail a exactement un correspondant */
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
			else
				exit_error("No correspondance for portal(s)", cub3d);
		}
		i++;
	}
	cub3d->nb_portals = cpt;
}

/* Remplace tous les portails par des zéros dans la carte */
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

/* Accède sécurisé à la carte en évitant les débordements */
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

/* Copie une chaîne dans une autre */
char	*ft_strcpy(char *dest, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
