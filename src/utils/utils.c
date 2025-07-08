/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:54:49 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 17:33:01 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	exit_error(char *err, t_cub3d *cub3d)
{
	int	i;

	(void)cub3d;
	write(2, "Error\n", 6);
	i = 0;
	while (err[i])
	{
		write(2, &err[i], 1);
		i++;
	}
	write(2, "\n", 1);
	//ft_free(cub3d);
	exit(1);
}

void	print_map(char **map, t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		printf("%s", map[i]);
		i++;
	}
	if (!map)
		exit_error("print map error map nulle", cub3d);
}