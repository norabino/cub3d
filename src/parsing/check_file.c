/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:48:42 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/07 19:27:31 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_check_textures(char **file)
{
	ft_strchr();
	return (1);
}

int	ft_check_colors(char **map)
{

	return (1);
}

int	ft_check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			
		}
		i++;
	}
	return (1);
}

int	ft_check_file(t_cubed cubed)
{
	if (!ft_check_textures(cub3d.textures))
		ft_perror("error textures\n");
	ft_check_colors(cub3d.colors);
	ft_check_map(cub3d.map);
	return(1);
}