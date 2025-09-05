/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/05 02:29:22 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Vérifie toutes les couleurs dans le fichier de configuration */
int	ft_check_colors(t_colors *colors, char **file, int *idx)
{
	int	i;

	i = 0;
	(*idx) = 0;
	while (file[i])
	{
		process_color_line(colors, file[i], idx, i);
		i++;
	}
	verify_colors(colors);
	return (1);
}
