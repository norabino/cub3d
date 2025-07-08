/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:48:42 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 11:50:39 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_all_text(t_textures textures)
{
	char	*tmp;

	tmp = ft_substr(textures.north, 0, 5);
	if (ft_strcmp(tmp, "NO ./"))
		return (free(tmp), 0);
	free(tmp);
	tmp = ft_substr(textures.south, 0, 5);
	if (ft_strcmp(tmp, "SO ./"))
		return (free(tmp), 0);
	free(tmp);
	tmp = ft_substr(textures.west, 0, 5);
	if (ft_strcmp(tmp, "WE ./"))
		return (free(tmp), 0);
	free(tmp);
	tmp = ft_substr(textures.east, 0, 5);
	if (ft_strcmp(tmp, "EA ./"))
		return (free(tmp), 0);
	free(tmp);
	return (1);

}

int	ft_check_textures(t_textures *textures)
{
	if (!check_all_text(*textures))
		return (0);
	textures->north = ft_substr(textures->north, 3, ft_strlen(textures->north) - 3);
	textures->south = ft_substr(textures->south, 3, ft_strlen(textures->south) - 3);
	textures->west = ft_substr(textures->west, 3, ft_strlen(textures->west) - 3);
	textures->east = ft_substr(textures->east, 3, ft_strlen(textures->east) - 3);
	return (1);
}

int	ft_check_colors(t)
{
	if (!check_all_colors(*))
	return (1);
}

int	ft_is_spawn(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	ft_check_letter(char **map)
{
	int	i;
	int	j;
	int	nb_spawn;
	
	i = 0;
	nb_spawn = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_is_spawn(map[i][j]))
				nb_spawn++;
			j++;
		}
		i++;
	}
	if (nb_spawn < 1)
		ft_perror("No spawn in map !!\nMust be one.");
	if (nb_spawn > 1)
		ft_perror("Multiple spawn in map !!\nMust be one.");
}

char **ft_map_adjustment(char **old)
{
	int	i;
	int	j;
	int	in_map;
	int	space;

	i = 0;
	in_map = 0;
	space = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (in_map && map[i][j] == ' ')
				ft_memmove(map[i][j], ,ft_strlen(map[i]));
			j++;
		}
		i++;
	}
	return (new);
}

int	ft_check_map(char **map)
{
	char	**work_map;
	
	ft_check_letter(map);
	work_map = ft_map_adjustment(map_cpy(map));
	
	return (1);
}

int	ft_check_file(t_cubed cubed)
{
	if (!ft_check_textures(cubed.textures))
		ft_perror("error textures\n");
	ft_check_colors(cubed.colors);
	ft_check_map(cub3d.map);
	return(1);
}