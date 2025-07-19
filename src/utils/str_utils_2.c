/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:14 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/19 21:05:45 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int	in_map(char c)
{
	if (is_letter(c) || c == '1' || c == '0')
		return (1);
	return (0);
}

t_off	collen(char **map, int y, int x)
{
	int	top;
	int	bottom;
	int	i;

	top = 0;
	bottom = 0;
	i = y;
	while (i > -1 && in_map(map[i][x]))
	{
		top++;
		i--;
	}
	i = y + 1;
	while (map[i] && map[i][x] && in_map(map[i][x]))
	{
		bottom++;
		i++;
	}
	return ((t_off){top - 1, top + bottom - 1});
}

t_off	linelen(char **map, int y, int x)
{
	int	right;
	int	left;
	int	i;

	right = 0;
	left = 0;
	i = x;
	while (i > -1 && in_map(map[y][i]))
	{
		left++;
		i--;
	}
	i = x + 1;
	while (map[y][i] && in_map(map[y][i]))
	{
		right++;
		i++;
	}
	return ((t_off){left, left + right});
}

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
			if (is_letter(cub3d->map[y][x]))
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
