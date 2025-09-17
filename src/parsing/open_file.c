/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:43:09 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/17 22:43:42 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Extrait l'extension d'un nom de fichier */
static char	*extract_extension(char *filename)
{
	char	*ext;
	int		i;
	int		y;

	i = ft_strlen(filename) - 1;
	while (i && filename[i] != '.')
		i--;
	y = i;
	while (filename[y] >= 32)
		y++;
	ext = ft_strndup(&filename[i], (y - i));
	return (ext);
}

/* Vérifie si l'extension du fichier est correcte */
int	check_extension(char *filename, char *extension)
{
	char	*ext;

	ext = extract_extension(filename);
	if (!ext || !ft_strcmp(ext, filename))
	{
		if (ext)
			free(ext);
		return (0);
	}
	if (ft_strcmp(ext, extension))
	{
		free(ext);
		return (0);
	}
	free(ext);
	return (1);
}

/* Alloue la mémoire pour stocker un fichier */
char	**malloc_file(t_cub3d *cub3d, char *filename)
{
	char	**file;
	int		fd;
	int		nb_lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Error when opening file...", cub3d);
	nb_lines = count_file_lines(fd);
	close(fd);
	file = (char **)calloc(nb_lines + 1, sizeof(char *));
	if (!file)
		exit_error("Error allocating file memory...", cub3d);
	return (file);
}

/* Lit toutes les lignes d'un fichier */
void	read_file_lines(char **file, int fd)
{
	int	i;

	i = 0;
	file[i] = get_next_line(fd);
	while (file[i])
	{
		i++;
		file[i] = get_next_line(fd);
	}
	file[i] = NULL;
}

/* Ouvre et lit un fichier complet en mémoire */
char	**open_file(t_cub3d *cub3d, char *filename)
{
	int		fd;
	char	**file;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Error when opening file...", cub3d);
	file = malloc_file(cub3d, filename);
	if (!file)
		exit_error("Error allocating file memory...", cub3d);
	read_file_lines(file, fd);
	close(fd);
	return (file);
}
