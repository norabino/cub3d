/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:45:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 16:44:15 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Convertit une chaîne en entier avec validation */
int	ft_atoi(char *str)
{
	int	res;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	res = 0;
	if (!only_numbers(str) || !is_nbr(str))
		return (-1);
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

/* Vérifie si un caractère appartient à la carte (mur ou espace vide) */
int	in_map(char c)
{
	if (c == '1' || c == '0')
		return (1);
	return (0);
}

/* Vérifie si un caractère est une position de départ du joueur */
int	is_player_spawn(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

/* Vérifie qu'il y a exactement une position de départ sur la carte */
void	ft_check_letter(t_cub3d *cub3d)
{
	int	y;
	int	x;
	int	nb_spawn;

	y = 0;
	nb_spawn = 0;
	while (cub3d->map[y])
	{
		x = 0;
		while (cub3d->map[y][x])
		{
			if (is_player_spawn(cub3d->map[y][x]))
				nb_spawn++;
			x++;
		}
		y++;
	}
	if (nb_spawn < 1)
		exit_error("No spawn in map !!\nMust be one.", cub3d);
	if (nb_spawn > 1)
		exit_error("Multiple spawn in map !!\nMust be one.", cub3d);
}