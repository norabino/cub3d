/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:31 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/05 02:29:22 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Gère les erreurs de textures dupliquées */
static void	texture_duplicate(char c, t_textures *textures)
{
	if (c == 'N')
		exit_error("Duplicate north texture", textures->cub3d);
	else if (c == 'S')
		exit_error("Duplicate south texture", textures->cub3d);
	else if (c == 'W')
		exit_error("Duplicate west texture", textures->cub3d);
	else if (c == 'E')
		exit_error("Duplicate east texture", textures->cub3d);
	else if (c == 'F')
		exit_error("Duplicate floor texture", textures->cub3d);
	else if (c == 'C')
		exit_error("Duplicate ceiling texture", textures->cub3d);
}

static char	*clean_texture_string(char *line, int j)
{
	char	*sub;
	int		len;
	int		i;

	sub = ft_substr(line, j, ft_strlen(line) - j, 0);
	len = ft_strlen(sub);
	i = len - 1;
	while (i >= 0 && (sub[i] == ' ' || sub[i] == '\t' || sub[i] == '\n'
			|| sub[i] == '\r'))
	{
		sub[i] = '\0';
		i--;
	}
	return (sub);
}

static void	assign_texture_path(char c, char *sub, t_textures *textures)
{
	if (c == 'N' && textures->north == NULL)
		textures->north = sub;
	else if (c == 'S' && textures->south == NULL)
		textures->south = sub;
	else if (c == 'W' && textures->west == NULL)
		textures->west = sub;
	else if (c == 'E' && textures->east == NULL)
		textures->east = sub;
	else if (c == 'F' && textures->floor == NULL)
		textures->floor = sub;
	else if (c == 'C' && textures->ceiling == NULL)
		textures->ceiling = sub;
	else
		free(sub);
}

void	assign_texture(char c, int j, char *line, t_textures *textures)
{
	char	*sub;

	sub = clean_texture_string(line, j);
	assign_texture_path(c, sub, textures);
}

int	parse_texture_line(t_cub3d *cub3d, char *line, t_textures *textures)
{
	int		j;
	int		z;

	j = 0;
	skip_spaces(line, &j);
	if ((line[j] == 'N' && textures->north != NULL)
		|| (line[j] == 'S' && textures->south != NULL)
		|| (line[j] == 'W' && textures->west != NULL)
		|| (line[j] == 'E' && textures->east != NULL)
		|| (line[j] == 'F' && textures->floor != NULL)
		|| (line[j] == 'C' && textures->ceiling != NULL))
		texture_duplicate(line[j], textures);
	if (is_letter(line[j]))
	{
		z = j;
		j += skip_letter(line[j], line[j + 1]);
		skip_spaces(line, &j);
		process_texture_path_found(cub3d, line, j, z);
	}
	return (all_text_set(*textures));
}
