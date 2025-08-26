/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:30:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/26 19:07:51 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Convertit un nombre entier en chaîne de caractères
** Comme écrire un nombre sur une feuille de papier
** chiffre par chiffre
*/
static int	convert_int_to_string(int fps_int, char *fps_str, int i)
{
	int	temp;

	if (fps_int == 0)
		fps_str[i++] = '0';
	else
	{
		temp = fps_int;
		while (temp > 0)
		{
			temp /= 10;
			i++;
		}
		temp = i - 1;
		while (fps_int > 0)
		{
			fps_str[temp--] = (fps_int % 10) + '0';
			fps_int /= 10;
		}
	}
	return (i);
}

/*
** Affiche les FPS en haut à droite de l'écran en vert
** Comme un indicateur lumineux sur un tableau de bord
** qui nous montre les performances en temps réel
*/
void	display_fps(t_cub3d *cub3d)
{
	char	fps_str[20];
	int		i;
	int		fps_int;

	fps_int = (int)(cub3d->current_fps + 0.5);
	i = 0;
	fps_str[i++] = 'F';
	fps_str[i++] = 'P';
	fps_str[i++] = 'S';
	fps_str[i++] = ':';
	fps_str[i++] = ' ';
	i = convert_int_to_string(fps_int, fps_str, i);
	fps_str[i] = '\0';
	mlx_string_put(cub3d->mlx.mlx, cub3d->mlx.win,
		SCREEN_WIDTH - 80, 25, 0x00FF00, fps_str);
}
