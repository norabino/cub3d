/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:43:09 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/07 18:46:46 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cubed.h"

int	check_extension(char *filename)
{
	char	*ext;
	int		i;

	i = ft_strlen(filename) - 1;
	while (i && filename[i] != '.')
		i--;
	ext = ft_strdup(&filename[i]);
	if (!ext || !ft_strcmp(ext, filename))
		return (ft_perror("No file extension.\n"), 0);
	if (ft_strcmp(ext, ".cub"))
		return (ft_perror("Wrong file extension.\n"), 0);
	return (1);
}

char	**malloc_map(char *filename)
{
	char	**map;
	int		fd;
	int		nb_lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_perror("Error when opening file...\n"), NULL);
	nb_lines = 0;
	while (get_next_line(fd))
		nb_lines++;
	map = (char **)malloc(sizeof(char *) * (nb_lines) + 1);
	return (map);
}

char	**open_map(char *filename)
{
	int		fd;
	char	**map;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_perror("Error when opening file...\n"), NULL);
	map = malloc_map(filename);
	i = 0;
	map[i] = get_next_line(fd);
	while (map[i])
	{
		i++;
		map[i] = get_next_line(fd);
	}
	return (map);
}
