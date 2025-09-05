/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/05 01:44:57 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Compte le nombre de lignes dans un fichier */
int	count_file_lines(int fd)
{
	char	*s_line;
	int		nb_lines;

	nb_lines = 0;
	s_line = get_next_line(fd);
	while (s_line)
	{
		free(s_line);
		nb_lines++;
		s_line = get_next_line(fd);
	}
	return (nb_lines);
}
