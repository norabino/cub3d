/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/19 21:32:51 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	handle_duplicate(char c, t_textures *textures)
{
	if (c == 'N')
		exit_error("Duplicate north texture", textures->cub3d);
	else if (c == 'S')
		exit_error("Duplicate south texture", textures->cub3d);
	else if (c == 'W')
		exit_error("Duplicate west texture", textures->cub3d);
	else if (c == 'E')
		exit_error("Duplicate east texture", textures->cub3d);
}

static void	set_texture(char c, int j, char *line, t_textures *textures)
{
	if (c == 'N' && textures->north == NULL)
		textures->north = ft_substr(line, j, ft_strlen(line) - j, 0);
	else if (c == 'S' && textures->south == NULL)
		textures->south = ft_substr(line, j, ft_strlen(line) - j, 0);
	else if (c == 'W' && textures->west == NULL)
		textures->west = ft_substr(line, j, ft_strlen(line) - j, 0);
	else if (c == 'E' && textures->east == NULL)
		textures->east = ft_substr(line, j, ft_strlen(line) - j, 0);
}

static int	check_line(char *line, t_textures *textures)
{
	int	j;
	int	z;

	j = 0;
	skip_spaces(line, &j);
	if ((line[j] == 'N' && textures->north != NULL)
		|| (line[j] == 'S' && textures->south != NULL)
		|| (line[j] == 'W' && textures->west != NULL)
		|| (line[j] == 'E' && textures->east != NULL))
		handle_duplicate(line[j], textures);
	else if (is_letter(line[j]))
	{
		z = j;
		j += skip_letter(line[j], line[j + 1]);
		skip_spaces(line, &j);
		set_texture(line[z], j, line, textures);
	}
	return (all_text_set(*textures));
}

int	ft_check_textures(t_textures *textures, char **file, int *idx)
{
	int	i;

	i = 0;
	*idx = 0;
	while (file[i])
	{
		if (*idx == 0 && check_line(file[i], textures))
			*idx = i + 1;
		i++;
	}
	if (!all_text_set(*textures))
		exit_error("Missing texture", textures->cub3d);
	return (1);
}
