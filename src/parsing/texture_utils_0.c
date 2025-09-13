/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/13 11:59:46 by norabino         ###   ########.fr       */
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
void	process_texture_path_found(t_cub3d *cub3d, int j, int z, int i)
{
	char	*filename;

	extract_filename_from_line(cub3d->file[i], j, &filename);
	if ((cub3d->file[i][z] == 'P') || (is_valid_file_path(filename)
			&& check_extension(cub3d, filename, ".xpm")
			&& try_to_open(filename)))
	{
		free(filename);
		set_texture(cub3d->file[i][z], j, cub3d->file[i], cub3d);
	}
	else
	{
		free(filename);
		cub3d->invalid_arg = ft_strdup(cub3d->file[i]);
		cub3d->nb_error_line = i;
		exit_error("Wrong texture path", cub3d);
	}
}

/* Traite une ligne de texture et met à jour l'état de validation */
int	process_single_texture_line(t_cub3d *cub3d, int i,
	int *found_all)
{
	if (!(*found_all) && parse_texture_line(cub3d, i))
	{
		*found_all = 1;
		return (i + 1);
	}
	else if (*found_all)
		parse_texture_line(cub3d, i);
	return (-1);
}

/* Vérifie que toutes les cub3d->textures sont définies et valides */
int	all_text_set(t_cub3d *cub3d)
{
	if (!cub3d->textures.north || !cub3d->textures.south
		|| !cub3d->textures.west || !cub3d->textures.east)
		return (0);
	if (!check_extension(cub3d, cub3d->textures.north, ".xpm"))
		exit_error("Wrong north texture extension.", cub3d);
	if (!check_extension(cub3d, cub3d->textures.south, ".xpm"))
		exit_error("Wrong south texture extension.", cub3d);
	if (!check_extension(cub3d, cub3d->textures.west, ".xpm"))
		exit_error("Wrong west texture extension.", cub3d);
	if (!check_extension(cub3d, cub3d->textures.east, ".xpm"))
		exit_error("Wrong east texture extension.", cub3d);
	if (cub3d->textures.floor && !check_extension(cub3d,
			cub3d->textures.floor, ".xpm"))
		exit_error("Wrong floor texture extension.", cub3d);
	if (cub3d->textures.ceiling && !check_extension(cub3d,
			cub3d->textures.ceiling, ".xpm"))
		exit_error("Wrong ceiling texture extension.", cub3d);
	return (1);
}

/* Assigne une texture selon son identifiant */
void	set_texture(char c, int j, char *line, t_cub3d *cub3d)
{
	char	*sub;
	int		len;
	int		i;

	len = ft_strlen(line) - j;
	sub = ft_substr(line, j, len, 0);
	len = ft_strlen(sub);
	i = len - 1;
	while (i >= 0 && (sub[i] == ' ' || sub[i] == '\t'
			|| sub[i] == '\n' || sub[i] == '\r'))
	{
		sub[i] = '\0';
		i--;
	}
	if (c == 'N' && !cub3d->textures.north)
		cub3d->textures.north = sub;
	else if (c == 'S' && !cub3d->textures.south)
		cub3d->textures.south = sub;
	else if (c == 'W' && !cub3d->textures.west)
		cub3d->textures.west = sub;
	else if (c == 'E' && !cub3d->textures.east)
		cub3d->textures.east = sub;
	else if (c == 'P' && !cub3d->textures.portals)
		cub3d->textures.portals = sub;
	else if (c == 'F' && !cub3d->textures.floor)
		cub3d->textures.floor = sub;
	else if (c == 'C' && !cub3d->textures.ceiling)
		cub3d->textures.ceiling = sub;
	else
	{
		free(sub);
		exit_error("Duplicate or invalid texture identifier.", cub3d);
	}
}
