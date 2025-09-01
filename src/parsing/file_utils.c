/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/01 21:01:40 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
