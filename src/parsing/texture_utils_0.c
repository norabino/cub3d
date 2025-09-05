/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/05 17:37:44 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Extrait le nom de fichier d'une ligne de configuration */
int	extract_filename_from_line(char *line, int j, char **filename)
{
	int	len;
	int	i;

	*filename = ft_substr(line, j, ft_strlen(line) - j, 0);
	len = ft_strlen(*filename);
	i = len - 1;
	while (i >= 0 && ((*filename)[i] == ' ' || (*filename)[i] == '\t'
			|| (*filename)[i] == '\n' || (*filename)[i] == '\r'))
	{
		(*filename)[i] = '\0';
		i--;
	}
	return (1);
}

/* Vérifie si la chaîne contient un chemin de fichier valide */
int	is_valid_file_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/' || str[i] == '.')
			return (1);
		i++;
	}
	return (0);
}

/* Traite un chemin de texture trouvé dans une ligne */
void	process_texture_path_found(t_cub3d *cub3d, char *line, int j, int z)
{
	char	*filename;

	extract_filename_from_line(line, j, &filename);
	if ((line[z] == 'P') || (is_valid_file_path(filename)
		&& check_extension(cub3d, filename, ".xpm")))
	{
		free(filename);
		set_texture(line[z], j, line, &cub3d->textures);
	}
	else
		free(filename);
}

/* Traite une ligne de texture et met à jour l'état de validation */
int	process_single_texture_line(t_cub3d *cub3d, char **file, int i,
	int *found_all)
{
	if (!(*found_all) && parse_texture_line(cub3d, file[i], &cub3d->textures))
	{
		*found_all = 1;
		return (i + 1);
	}
	else if (*found_all)
		parse_texture_line(cub3d, file[i], &cub3d->textures);
	return (-1);
}

/* Vérifie que toutes les textures sont définies et valides */
int	all_text_set(t_textures textures)
{
	if (!textures.north || !textures.south || !textures.west
		|| !textures.east)
		return (0);
	if (!check_extension(textures.cub3d, textures.north, ".xpm"))
		exit_error("Wrong north texture extension.", textures.cub3d);
	if (!check_extension(textures.cub3d, textures.south, ".xpm"))
		exit_error("Wrong south texture extension.", textures.cub3d);
	if (!check_extension(textures.cub3d, textures.west, ".xpm"))
		exit_error("Wrong west texture extension.", textures.cub3d);
	if (!check_extension(textures.cub3d, textures.east, ".xpm"))
		exit_error("Wrong east texture extension.", textures.cub3d);
	if (textures.floor && !check_extension(textures.cub3d,
			textures.floor, ".xpm"))
		exit_error("Wrong floor texture extension.", textures.cub3d);
	if (textures.ceiling && !check_extension(textures.cub3d,
			textures.ceiling, ".xpm"))
		exit_error("Wrong ceiling texture extension.", textures.cub3d);
	return (1);
}

/* Assigne une texture selon son identifiant */
void	set_texture(char c, int j, char *line, t_textures *textures)
{
	char	*sub;
	int		len;
	int		i;

	len = ft_strlen(line) - j;
	sub = ft_substr(line, j, len, 0);
	len = ft_strlen(sub);
	i = len - 1;
	while (i >= 0 && (sub[i] == ' ' || sub[i] == '\t' || sub[i] == '\n' || sub[i] == '\r'))
	{
		sub[i] = '\0';
		i--;
	}
	if (c == 'N' && !textures->north)
		textures->north = sub;
	else if (c == 'S' && !textures->south)
		textures->south = sub;
	else if (c == 'W' && !textures->west)
		textures->west = sub;
	else if (c == 'E' && !textures->east)
		textures->east = sub;
	else if (c == 'P' && !textures->portals)
		textures->portals = sub;
	else
	{
		free(sub);
		exit_error("Duplicate or invalid texture identifier.", textures->cub3d);
	}
}
