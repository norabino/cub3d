/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:43:09 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 17:58:35 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_extension(t_cub3d *cub3d, char *filename)
{
	char	*ext;
	int		i;

	i = ft_strlen(filename) - 1;
	while (i && filename[i] != '.')
		i--;
	ext = ft_strdup(&filename[i]);
	if (!ext || !ft_strcmp(ext, filename))
		exit_error("No file extension.", cub3d);
	if (ft_strcmp(ext, ".cub"))
		exit_error("Wrong file extension.", cub3d);
	return (1);
}

char	**malloc_file(t_cub3d *cub3d, char *filename)
{
	char	**file;
	int		fd;
	int		nb_lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Error when opening file...", cub3d);
	nb_lines = 0;
	while (get_next_line(fd))
		nb_lines++;
	file = (char **)malloc(sizeof(char *) * (nb_lines) + 1);
	return (file);
}

char	**open_file(t_cub3d *cub3d, char *filename)
{
	int		fd;
	char	**file;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Error when opening file...", cub3d);
	file = malloc_file(cub3d, filename);
	i = 0;
	file[i] = get_next_line(fd);
	while (file[i])
	{
		i++;
		file[i] = get_next_line(fd);
	}
	file[i] = NULL;
	return (file);
}
